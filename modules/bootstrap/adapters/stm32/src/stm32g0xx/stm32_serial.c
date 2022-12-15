/**
  ******************************************************************************
  * @file   stm32_serial.c
  * @author Jonathan Taylor
  * @date   12/14/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32_serial.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32_dma.h"
#include "stm32_nvic.h"
#include "stm32g0xx_interface.h"

static struct
{
    serial_base_t    base;
    volatile uint8_t rx_buffer[RX_BUFFER_SIZE];
    uint16_t dma_pos_old;
    uint16_t dma_pos_new;
#if STM32_USART_DMA_BUFFER_SIZE
    uint8_t  dma_buffer[STM32_USART_DMA_BUFFER_SIZE];
    uint16_t (*rx_callback)(uint16_t size);
#endif
} self = {0};

static void uart_clock_init();

static void gpio_init();

static void uart_init();

#if STM32_USART_RX_DMA || STM32_USART_TX_DMA
static void dma_init();
#endif

static void nvic_init();

static void open(void * instance);

static void close(void * instance);

static uint16_t read(void * instance, uint8_t * bytes);

static void write(void * instance, uint8_t * bytes, uint16_t size);

static void _putchar(void * instance, uint8_t a);

static void stm32_dma_transfer(uint16_t size);

static serial_interface_t interface = {
        .open=open,
        .close=close,
        .read=read,
        .write=write,
        .putchar=_putchar
};

Serial
stm32_serial_create()
{
    self.base.vtable      = &interface;
    self.base.rx_buffer = self.rx_buffer;
    self.base.buffer_position = 0;
    self.dma_pos_new = 0;
    self.dma_pos_old = 0;
    uart_clock_init();
    gpio_init();
    dma_init();
    nvic_init();
    uart_init();
    LL_GPIO_ResetOutputPin(DE_PORT, RE_PIN);
    self.base.buffer_size = RX_BUFFER_SIZE;
    return &self.base;
}

static void
open(void * instance)
{

}

static void
close(void * instance)
{
    LL_USART_Disable((USART_TypeDef *) instance);
}

static uint16_t
read(void * instance, uint8_t * bytes)
{
    return 0;
}

static void
write(void * instance, uint8_t * bytes, uint16_t size)
{
    /** @todo make this use gpio interface library and not call stm directly */
    LL_GPIO_SetOutputPin(DE_PORT, RE_PIN);
    while (!LL_GPIO_IsOutputPinSet(DE_PORT, RE_PIN));
    for (uint16_t i = 0; i < size; i++)
    {
        LL_USART_TransmitData8((USART_TypeDef *) instance, bytes[i]);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF((USART_TypeDef *)instance));
    }
}

static void
_putchar(void * instance, uint8_t a)
{
    LL_GPIO_SetOutputPin(DE_PORT, RE_PIN);
#ifndef SIMULATED
    while (!LL_GPIO_IsOutputPinSet(DE_PORT, RE_PIN));
#endif
    LL_USART_TransmitData8((USART_TypeDef *) instance, a);
#ifndef SIMULATED
    while (!LL_USART_IsActiveFlag_TXE_TXFNF((USART_TypeDef *)instance));
#endif
}

static void
uart_clock_init()
{
    LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
}

static void
gpio_init()
{
    LL_GPIO_InitTypeDef gpio_params;

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
uart_init()
{
    LL_USART_InitTypeDef uart_params = {
            .PrescalerValue=STM32_PRESCALER_VALUE,
            .BaudRate=STM32_BAUD_RATE,
            .DataWidth=STM32_DATA_WIDTH,
            .StopBits=STM32_STOP_BITS,
            .Parity=STM32_PARITY,
            .TransferDirection=STM32_TRANSFER_DIRECTION,
            .HardwareFlowControl=STM32_HARDWARE_FLOW_CONTROL,
            .OverSampling=STM32_OVER_SAMPLING
    };

#if STM32_ENABLE_USART1
    LL_USART_Init(USART1, &uart_params);

#if STM32_USART1_RS485
    LL_USART_EnableDEMode(USART1);
    LL_USART_SetDESignalPolarity(USART1, STM32_DE_POLARITY);
    LL_USART_SetDEAssertionTime(USART1, STM32_DE_ASSERTION_TIME);
    LL_USART_SetDEDeassertionTime(USART1, STM32_DE_DEASSERTION_TIME);

#endif // STM32_USART1_RS485

#if STM32_USART1_FIFO
    LL_USART_EnableFIFO(USART1);
#else
    LL_USART_DisableFIFO(USART1);
#endif // STM32_USART1_FIFO

#if STM32_USART1_ASYNC
    LL_USART_ConfigAsyncMode(USART1);
#endif // STM32_USART1_ASYNC

#if STM32_USART_RX_DMA
    LL_USART_EnableDMAReq_RX(USART1);
#else
    LL_USART_DisableDMAReq_RX(USART1);

#endif // STM32_USART_RX_DMA

#if STM32_USART_TX_DMA

    LL_USART_EnableDMAReq_TX(USART1);
#else
    LL_USART_DisableDMAReq_TX(USART1);

#endif // STM32_USART_TX_DMA

    LL_USART_Enable(USART1);
#ifndef SIMULATED
    while ((!(LL_USART_IsActiveFlag_TEACK(USART1))
           || (!(LL_USART_IsActiveFlag_REACK(USART1)))))
    {}
#endif


#if STM32_USART_RTO_ENABLE
    LL_USART_SetRxTimeout(USART1, STM32_RX_TIMEOUT);
    LL_USART_EnableRxTimeout(USART1);
    LL_USART_ClearFlag_RTO(USART1);

#ifndef SIMULATED
    while(LL_USART_IsActiveFlag_RTO(USART1));
#endif
    LL_USART_EnableIT_RTO(USART1);
#else
#endif //STM32_USART_RTO_ENABLE

    LL_USART_DisableIT_PE(USART1);
    LL_USART_DisableIT_ERROR(USART1);

#if STM32_USART_TC_ENABLE
    LL_USART_ClearFlag_TC(USART1);
#ifndef SIMULATED
    while(LL_USART_IsActiveFlag_TC(USART1));
#endif
    LL_USART_EnableIT_TC(USART1);
#else
    LL_USART_DisableIT_TC(USART1);
#endif //STM32_USART_TC_ENABLE

#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
    LL_USART_Init(USART1, &uart_params);

#if STM32_USART1_FIFO
    LL_USART_EnableFIFO(USART2);
#else
    LL_USART_DisableFIFO(USART2);
#endif // STM32_USART1_FIFO

#if STM32_USART2_ASYNC
    LL_USART_ConfigAsyncMode(USART2);
#endif // STM32_USART1_ASYNC

#endif // STM32_ENABLE_USART2
}

static void
dma_init()
{
    stm32_dma_params_t dma_init = {
            .dma=DMA1,
            .channel=RX_CHANNEL,
            .periph_address=(uint32_t) &USART1->RDR,
            .memory_address=(uint32_t) self.rx_buffer,
            .data_length=STM32_USART_DMA_BUFFER_SIZE,
            .transfer_direction=LL_DMA_DIRECTION_PERIPH_TO_MEMORY,
            .circular=false,
            .periph_request=LL_DMAMUX_REQ_USART1_RX,
            .enable_ht=false,
            .enable_tc=true,
    };
    stm32_dma_init(&dma_init);
}

static void
nvic_init()
{
    stm32_nvic_init(DMA1_Channel1_IRQn, 0);
    stm32_nvic_init(USART1_IRQn, 1);
}

static void
stm32_dma_transfer(uint16_t size)
{
    self.dma_pos_old = self.dma_pos_new;

    if (self.dma_pos_old + size > RX_BUFFER_SIZE)
    {
        uint16_t space = RX_BUFFER_SIZE - self.dma_pos_old;
        copy(self.rx_buffer + self.dma_pos_old, self.dma_buffer, space);
        self.dma_pos_old = 0;
        self.dma_pos_new = size - space;
        copy(self.rx_buffer, self.dma_buffer + space, self.dma_pos_new);
    } else
    {
        copy(self.rx_buffer + self.dma_pos_old, self.dma_buffer, size);
        self.dma_pos_new = size + self.dma_pos_old;
    }
}


__INTERRUPT
DMA1_Channel1_IRQHandler(void)
{
    stm32_dma_transfer(STM32_USART_DMA_BUFFER_SIZE);
    LL_DMA_ClearFlag_TC1(DMA1);
    self.base.buffer_position += STM32_USART_DMA_BUFFER_SIZE;
    LL_DMA_DisableChannel(RX_DMA, RX_CHANNEL);
    LL_DMA_SetDataLength(RX_DMA, RX_CHANNEL, STM32_USART_DMA_BUFFER_SIZE);
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
        if (DMA1_Channel1->CNDTR != STM32_USART_DMA_BUFFER_SIZE)
        {
            if (LL_DMA_IsActiveFlag_TC1(DMA1)) return;
            uint16_t size       = STM32_USART_DMA_BUFFER_SIZE - DMA1_Channel1->CNDTR;
            stm32_dma_transfer(size);
            self.base.buffer_position += self.dma_pos_new;
            self.base.buffer_position = self.rx_callback(self.base.buffer_position);
        }
        LL_USART_ClearFlag_RTO(USART1);
    }
}