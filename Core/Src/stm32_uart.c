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
#include "stm32_uart.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_usart.h"

#define BAUD 115200

static struct stm32_serial_t
{
    uint8_t       dma_buffer[10];
    sized_array_t rx_buffer;
} self = {0};

static bool stm32_serial_read(sized_array_t * data);

static bool
stm32_serial_write(const sized_array_t * data);

static void stm32_serial_gpio_init();

static void stm32_serial_uart_init();

static void stm32_serial_dma_init(uint32_t channel);

static void stm32_serial_nvic_init();

static serial_interface_t stm32_serial_interface = {
        .read = stm32_serial_read,
        .write = stm32_serial_write
};

void
stm32_serial_create(Serial base, uint8_t * rx_buffer)
{
    base->vtable         = &stm32_serial_interface;
    base->baud           = BAUD;
    self.rx_buffer.bytes = rx_buffer;
    stm32_serial_gpio_init();
    stm32_serial_dma_init(RX_CHANNEL);
    //stm32_serial_dma_init(self, TX_CHANNEL);
    stm32_serial_nvic_init();
    stm32_serial_uart_init();
    LL_GPIO_ResetOutputPin(DE_PORT, RE_PIN);
}

uint16_t
stm32_serial_received_len()
{
    self.rx_buffer.size = 100
                          - LL_DMA_GetDataLength(
                                  DMA1,
                                  RX_CHANNEL
                          );

    return self.rx_buffer.size;
}

static bool
stm32_serial_read(sized_array_t * data)
{
    data->size      = self.rx_buffer.size;
    for (uint16_t i = 0; i < data->size; i++)
        self.rx_buffer.bytes[i] = self.dma_buffer[i];
    data->bytes = self.rx_buffer.bytes;
    return data->size > 0;
}

static bool
stm32_serial_write(const sized_array_t * data)
{
    LL_GPIO_SetOutputPin(DE_PORT, RE_PIN);
    while (!LL_GPIO_IsOutputPinSet(DE_PORT, RE_PIN));
    for (uint16_t i = 0; i < data->size; i++)
    {
        uint8_t v = data->bytes[i];
        LL_USART_TransmitData8(USART1, v);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF(USART1));
    }
    while (!LL_USART_IsActiveFlag_TC(USART1));
    LL_GPIO_ResetOutputPin(DE_PORT, RE_PIN);
    while (LL_GPIO_IsOutputPinSet(DE_PORT, RE_PIN));
    return true;
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
    usart_params.OverSampling        = LL_USART_OVERSAMPLING_16;

    LL_USART_Init(USART1, &usart_params);

    LL_USART_EnableDEMode(USART1);
    LL_USART_SetDESignalPolarity(USART1, LL_USART_DE_POLARITY_HIGH);
    LL_USART_SetDEAssertionTime(USART1, 0x08);
    LL_USART_SetDEDeassertionTime(USART1, 0x08);

    LL_USART_DisableFIFO(USART1);
    LL_USART_ConfigAsyncMode(USART1);
    LL_USART_EnableDMAReq_RX(USART1);

    LL_USART_Enable(USART1);
    while ((!(LL_USART_IsActiveFlag_TEACK(USART1)))
           || (!(LL_USART_IsActiveFlag_REACK(USART1))));
    LL_USART_EnableRxTimeout(USART1);

    LL_USART_SetRxTimeout(USART1, 100);
    LL_USART_ClearFlag_RTO(USART1);
    while (LL_USART_IsActiveFlag_RTO(USART1));
    LL_USART_EnableIT_RTO(USART1);
    //LL_USART_EnableIT_TC(USART1);
    LL_USART_ClearFlag_TC(USART1);
}

static void
stm32_serial_dma_init(uint32_t channel)
{
    LL_DMA_SetMode(
            DMA1,
            channel,
            LL_DMA_MODE_NORMAL
    );

    LL_DMA_SetPeriphIncMode(
            DMA1,
            channel,
            LL_DMA_PERIPH_NOINCREMENT
    );

    LL_DMA_SetMemoryIncMode(
            DMA1,
            channel,
            LL_DMA_MEMORY_INCREMENT
    );

    LL_DMA_SetPeriphSize(
            DMA1,
            channel,
            LL_DMA_PDATAALIGN_BYTE
    );

    LL_DMA_SetMemorySize(
            DMA1,
            channel,
            LL_DMA_MDATAALIGN_BYTE
    );
    if (RX_CHANNEL == channel)
    {
        LL_DMA_SetPeriphAddress(
                DMA1,
                channel,
                (uint32_t) &USART1->RDR
        );

        LL_DMA_SetMemoryAddress(
                DMA1,
                channel,
                (uint32_t) self.dma_buffer
        );

        LL_DMA_SetPeriphRequest(
                DMA1,
                channel,
                LL_DMAMUX_REQ_USART1_RX
        );

        LL_DMA_SetDataTransferDirection(
                DMA1,
                channel,
                LL_DMA_DIRECTION_PERIPH_TO_MEMORY
        );

        LL_DMA_SetDataLength(
                DMA1,
                channel,
                100
        );

        LL_DMA_EnableChannel(DMA1, RX_CHANNEL);
        LL_DMA_EnableIT_TC(DMA1, RX_CHANNEL);
    } else
    {
        LL_DMA_SetPeriphAddress(
                DMA1,
                channel,
                LL_USART_DMA_GetRegAddr(USART1, LL_USART_DMA_REG_DATA_TRANSMIT)
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
    }
    LL_DMA_SetChannelPriorityLevel(
            DMA1,
            channel,
            LL_DMA_PRIORITY_LOW
    );

}

static void
stm32_serial_nvic_init()
{
    NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);

    NVIC_SetPriority(USART1_IRQn, 0);
    NVIC_EnableIRQ(USART1_IRQn);
}
