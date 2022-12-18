/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include <memory.h>
#include "stm32_uart.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_usart.h"
#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g0xx/stm32_dma.h"
#include "stm32g0xx/stm32_nvic.h"

#define BAUD 115200
#define DMA_BUFF_SIZE 8
#define RX_TIMEOUT 39

typedef struct stm32_serial_pos_t
{
    volatile uint16_t old;
    volatile uint16_t new;
} stm32_serial_pos_t;

static struct stm32_serial_t
{
    serial_t base;
    volatile uint8_t * rx_buffer;
    volatile uint8_t * tx_buffer;
    uint16_t (*rx_callback)(uint16_t size);
    volatile uint8_t dma_buffer[DMA_BUFF_SIZE];
    volatile stm32_serial_pos_t buffer_pos;
    volatile stm32_serial_pos_t dma_pos;
} self = {0};

static void open(Serial serial);

static void close(Serial serial);

static uint16_t read(Serial serial, uint8_t * bytes);

static void write(Serial serial, uint8_t * bytes, uint16_t size);

static inline void stm32_serial_gpio_init();

static inline void stm32_serial_uart_init();

static inline void stm32_serial_dma_init();

static inline void stm32_serial_nvic_init();

static serial_interface_t stm32_serial_interface = {
        .open=open,
        .close=close,
        .read = read,
        .write =write
};

Serial
stm32_serial_create(stm32_serial_params_t * params)
{
    self.base.vtable = &stm32_serial_interface;
    self.rx_buffer         = params->rx_buffer;
    self.tx_buffer         = params->tx_buffer;

    stm32_serial_gpio_init();
    stm32_serial_dma_init();
    stm32_serial_nvic_init();
    stm32_serial_uart_init();
    LL_GPIO_ResetOutputPin(DE_PORT, RE_PIN);
    return (Serial) &self;
}

static inline volatile void
* copy(
        volatile uint8_t * restrict dest,
        const volatile uint8_t * restrict src,
        size_t n)
{
    const volatile uint8_t * src_c  = src;
    volatile uint8_t       * dest_c = dest;

    while (n > 0)
    {
        n--;
        dest_c[n] = src_c[n];
    }
    return dest;
}

static void
stm32_dma_transfer(uint16_t size)
{
    self.dma_pos.old = self.dma_pos.new;

    if (self.dma_pos.old + size > RX_BUFFER_SIZE)
    {
        uint16_t space = RX_BUFFER_SIZE - self.dma_pos.old;
        copy(self.rx_buffer + self.dma_pos.old, self.dma_buffer, space);
        self.dma_pos.old = 0;
        self.dma_pos.new = size - space;
        copy(self.rx_buffer, self.dma_buffer + space, self.dma_pos.new);
    } else
    {
        copy(self.rx_buffer + self.dma_pos.old, self.dma_buffer, size);
        self.dma_pos.new = size + self.dma_pos.old;
    }
}


static void
open(Serial serial)
{
    (void) serial;
    LL_DMA_EnableChannel(DMA1, RX_CHANNEL);
    LL_USART_Enable(USART1);
}

static void
close(Serial serial)
{
    (void) serial;
    LL_DMA_DisableChannel(DMA1, RX_CHANNEL);
    LL_USART_Disable(USART1);
}

static uint16_t
read(Serial base, uint8_t * bytes)
{
    (void) base;
    (void) bytes;
    return 0;
}

static void
write(Serial base, uint8_t * bytes, uint16_t size)
{
    (void) base;
    LL_GPIO_SetOutputPin(DE_PORT, RE_PIN);
    while (!LL_GPIO_IsOutputPinSet(DE_PORT, RE_PIN));
    for (uint16_t i = 0; i < size; i++)
    {
        LL_USART_TransmitData8(USART1, bytes[i]);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF(USART1));
    }
}

static void
stm32_serial_gpio_init()
{
    LL_GPIO_InitTypeDef gpio_params;

    LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

    gpio_params.Pin        = RX_PIN;
    gpio_params.Mode       = LL_GPIO_MODE_ALTERNATE;
    gpio_params.Speed      = LL_GPIO_SPEED_FREQ_LOW;
    gpio_params.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_params.Pull       = LL_GPIO_PULL_NO;
    gpio_params.Alternate  = LL_GPIO_AF_0;
    LL_GPIO_Init(RX_PORT, &gpio_params);

    gpio_params.Pin = TX_PIN;
    LL_GPIO_Init(TX_PORT, &gpio_params);

    gpio_params.Pin       = DE_PIN;
    gpio_params.Alternate = LL_GPIO_AF_1;
    LL_GPIO_Init(DE_PORT, &gpio_params);

    gpio_params.Pin       = RE_PIN;
    gpio_params.Mode      = LL_GPIO_MODE_OUTPUT;
    gpio_params.Alternate = 0;
    LL_GPIO_Init(DE_PORT, &gpio_params);
}

static void
stm32_serial_uart_init()
{
    LL_USART_InitTypeDef usart_params;
    usart_params.PrescalerValue      = LL_USART_PRESCALER_DIV1;
    usart_params.BaudRate            = BAUD;
    usart_params.DataWidth           = LL_USART_DATAWIDTH_8B;
    usart_params.StopBits            = LL_USART_STOPBITS_1;
    usart_params.Parity              = LL_USART_PARITY_NONE;
    usart_params.TransferDirection   = LL_USART_DIRECTION_TX_RX;
    usart_params.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    usart_params.OverSampling        = LL_USART_OVERSAMPLING_8;

    LL_USART_Init(USART1, &usart_params);

    LL_USART_EnableDEMode(USART1);
    LL_USART_SetDESignalPolarity(USART1, LL_USART_DE_POLARITY_HIGH);
    LL_USART_SetDEAssertionTime(USART1, 0x08);
    LL_USART_SetDEDeassertionTime(USART1, 0x08);

    LL_USART_DisableFIFO(USART1);
    LL_USART_ConfigAsyncMode(USART1);
    LL_USART_EnableDMAReq_RX(USART1);
    //LL_USART_EnableDMAReq_TX(USART1);

    LL_USART_Enable(USART1);
    while ((!(LL_USART_IsActiveFlag_TEACK(USART1)))
           || (!(LL_USART_IsActiveFlag_REACK(USART1))))
    {}
    LL_USART_SetRxTimeout(USART1, RX_TIMEOUT);
    LL_USART_EnableRxTimeout(USART1);
    LL_USART_ClearFlag_RTO(USART1);
    while (LL_USART_IsActiveFlag_RTO(USART1));
    LL_USART_EnableIT_RTO(USART1);
    LL_USART_DisableIT_PE(USART1);
    LL_USART_DisableIT_ERROR(USART1);
    LL_USART_ClearFlag_TC(USART1);
    //LL_USART_EnableIT_TXE_TXFNF(USART1);
    LL_USART_EnableIT_TC(USART1);
}

static inline void
stm32_serial_dma_init()
{
    stm32_dma_params_t dma_init = {
            .dma=DMA1,
            .channel=RX_CHANNEL,
            .periph_address=(uint32_t) &USART1->RDR,
            .memory_address=(uint32_t) self.rx_buffer,
            .data_length=DMA_BUFF_SIZE,
            .transfer_direction=LL_DMA_DIRECTION_PERIPH_TO_MEMORY,
            .circular=false,
            .periph_request=LL_DMAMUX_REQ_USART1_RX,
            .enable_ht=false,
            .enable_tc=true,
    };
    stm32_dma_init(&dma_init);
#if 0
    {
        LL_DMA_SetPeriphAddress(
                DMA1,
                channel,
                LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_TRANSMIT)
        );

        LL_DMA_SetMemoryAddress(
                DMA1,
                channel,
                (uint32_t) self.tx_buffer
        );

        LL_DMA_SetDataLength(
                DMA1,
                channel,
                6
        );
        LL_DMA_SetPeriphRequest(
                DMA1,
                channel,
                LL_DMAMUX_REQ_USART1_TX
        );

        LL_DMA_SetDataTransferDirection(
                DMA1,
                channel,
                LL_DMA_DIRECTION_MEMORY_TO_PERIPH
        );
        //LL_DMA_EnableIT_TC(DMA1, channel);
        LL_USART_ClearFlag_TC(USART1);
        LL_DMA_EnableChannel(DMA1, TX_CHANNEL);
    }
#endif
}

static void
stm32_serial_nvic_init()
{
    stm32_nvic_init(DMA1_Channel1_IRQn, 0);
    stm32_nvic_init(USART1_IRQn, 1);
}

__INTERRUPT
DMA1_Channel1_IRQHandler(void)
{
    stm32_dma_transfer(DMA_BUFF_SIZE);
    LL_DMA_ClearFlag_TC1(DMA1);
    self.buffer_pos.new += DMA_BUFF_SIZE;
    LL_DMA_DisableChannel(RX_DMA, RX_CHANNEL);
    LL_DMA_SetDataLength(RX_DMA, RX_CHANNEL, DMA_BUFF_SIZE);
    LL_DMA_EnableChannel(RX_DMA, RX_CHANNEL);
}

__INTERRUPT
USART1_IRQHandler(void)
{
    if (LL_USART_IsActiveFlag_TC(USART1))
    {
        LL_GPIO_ResetOutputPin(DE_PORT, RE_PIN);
        LL_USART_ClearFlag_TC(USART1);
    }
    if (LL_USART_IsActiveFlag_RXNE_RXFNE(USART1))
    {
        return;
    } else if (LL_USART_IsActiveFlag_RTO(USART1))
    {
        if (DMA1_Channel1->CNDTR != DMA_BUFF_SIZE)
        {
            if (LL_DMA_IsActiveFlag_TC1(DMA1)) return;
            uint16_t size       = DMA_BUFF_SIZE - DMA1_Channel1->CNDTR;
            stm32_dma_transfer(size);
            self.buffer_pos.new += self.dma_pos.new;
            self.buffer_pos.old = self.rx_callback(self.buffer_pos.new);
        }
        LL_USART_ClearFlag_RTO(USART1);
    }
}