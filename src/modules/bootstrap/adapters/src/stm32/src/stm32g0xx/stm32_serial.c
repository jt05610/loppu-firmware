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

#include "default/serial_config.h"
#include "default/gpio_config.h"
#include "stm32g0xx_ll_gpio.h"
#include "buffer.h"
#include "stm32g0xx_ll_dma.h"
#include "default/dma_config.h"
#include "stm32_interrupts.h"

static struct
{
    serial_base_t base;
    rx_callback_t * rx_callback;
} self = {0};

static inline void uart_init();

static inline void open(void * instance);

static inline void close(void * instance);

static inline uint16_t read(void * instance, uint8_t * bytes);

static inline void write(void * instance, uint8_t * bytes, uint16_t size);

static inline uint8_t _putchar(void * instance, char a);

static serial_interface_t interface = {
        .open=open,
        .close=close,
        .read=read,
        .write=write,
        .putchar=_putchar
};

#if STM32_ENABLE_USART1_RX_DMA
STATIC_CIRC_BUF(usart1_rx_circ, STM32_USART1_RX_BUFFER_SIZE);

uint8_t *
stm32_get_usart1_rx_buffer()
{
    return usart1_rx_circ_buffer;
}

# endif

#if STM32_ENABLE_USART1_TX_DMA
STATIC_CIRC_BUF(usart1_tx_circ, STM32_USART1_TX_BUFFER_SIZE);

uint8_t *
stm32_get_usart1_tx_buffer()
{
    return usart1_tx_circ_buffer;
}

#endif

#if STM32_ENABLE_USART2_RX_DMA
STATIC_CIRC_BUF(usart2_rx_circ, STM32_USART2_RX_BUFFER_SIZE);
uint8_t *
stm32_get_usart2_rx_buffer()
{
    return usart2_rx_circ_buffer;
}
# endif

#if STM32_ENABLE_USART2_TX_DMA
STATIC_CIRC_BUF(usart2_tx_circ, STM32_USART2_TX_BUFFER_SIZE);
uint8_t *
stm32_get_usart2_tx_buffer()
{
    return usart2_tx_circ_buffer;
}
#endif

Serial
stm32_serial_create()
{
    self.base.vtable        = &interface;
    self.base.serial_buffer = &usart1_rx_circ;
#ifndef SIMULATED
    LL_GPIO_ResetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
#endif
    uart_init();
    return &self.base;
}

void
stm32_serial_set_rto_cb(void * instance, rx_callback_t * cb, void * to_pass)
{
    self.rx_callback = cb;
}

static void
open(void * instance)
{
#if (STM32_ENABLE_USART1 & STM32_ENABLE_USART2)
#if STM32_ENABLE_USART1
    if ((USART_TypeDef *) instance == USART1) {
#if STM32_USART1_RX_ENABLE_DMA
        LL_DMA_EnableChannel(DMA1, STM32_USART1_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_USART1_TX_DMA
        LL_DMA_EnableChannel(DMA1, STM32_USART1_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA
    }
#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
    if ((USART_TypeDef *) instance == USART2) {
#if STM32_USART2_RX_ENABLE_DMA
        LL_DMA_EnableChannel(DMA1, STM32_USART2_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_USART2_TX_DMA
        LL_DMA_EnableChannel(DMA1, STM32_USART2_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA
    }
#endif // STM32_ENABLE_USART2

#else
#if STM32_ENABLE_USART1
#if STM32_USART1_RX_DMA
    LL_DMA_EnableChannel(DMA1, STM32_USART1_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_USART1_TX_DMA
    LL_DMA_EnableChannel(DMA1, STM32_USART1_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA

#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2

#if STM32_USART2_RX_DMA
    LL_DMA_EnableChannel(DMA1, STM32_USART2_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_USART2_TX_DMA
    LL_DMA_EnableChannel(DMA1, STM32_USART2_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA

#endif // STM32_ENABLE_USART2

#endif // STM32_ENABLE_USART1 & STM32_ENABLE_USART1
}

static void
close(void * instance)
{
    LL_USART_Disable((USART_TypeDef *) instance);
#if (STM32_ENABLE_USART1 & STM32_ENABLE_USART2)
#if STM32_ENABLE_USART1
    if ((USART_TypeDef *) instance == USART1) {
#if STM32_USART1_RX_ENABLE_DMA
        LL_DMA_DisableChannel(DMA1, STM32_USART1_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_USART1_TX_DMA
        LL_DMA_EnableChannel(DMA1, STM32_USART1_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA
    }
#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
    if ((USART_TypeDef *) instance == USART2) {
#if STM32_USART2_RX_ENABLE_DMA
        LL_DMA_DisableChannel(DMA1, STM32_USART2_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_USART2_TX_DMA
        LL_DMA_DisableChannel(DMA1, STM32_USART2_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA
    }
#endif // STM32_ENABLE_USART2

#else
#if STM32_ENABLE_USART1
#if STM32_USART1_RX_DMA
    LL_DMA_EnableChannel(DMA1, STM32_USART1_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_USART1_TX_DMA
    LL_DMA_EnableChannel(DMA1, STM32_USART1_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA

#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2

#if STM32_USART2_RX_DMA
    LL_DMA_EnableChannel(DMA1, STM32_USART2_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_USART2_TX_DMA
    LL_DMA_EnableChannel(DMA1, STM32_USART2_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA

#endif // STM32_ENABLE_USART2

#endif // STM32_ENABLE_USART1 & STM32_ENABLE_USART
}

static uint16_t
read(void * instance, uint8_t * bytes)
{
    return 0;
}

static void
write(void * instance, uint8_t * bytes, uint16_t size)
{
#if STM32_USART1_RS485
    LL_GPIO_SetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
#endif // STM32_USART1_RS485
#if STM32_ENABLE_USART1_TX_DMA
#else
    while (!LL_GPIO_IsOutputPinSet(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN));
    for (uint16_t i = 0; i < size; i++) {
        LL_USART_TransmitData8((USART_TypeDef *) instance, bytes[i]);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF((USART_TypeDef *) instance));
    }
#endif
}

static uint8_t
_putchar(void * instance, char a)
{
#if STM32_USART1_RS485
    LL_GPIO_SetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
#endif // STM32_USART1_RS485
#if STM32_ENABLE_USART1_TX_DMA
#else
    while (!LL_GPIO_IsOutputPinSet(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN));
        LL_USART_TransmitData8((USART_TypeDef *) instance, (uint8_t) a);
#endif
    return (uint8_t) a;
}

static void
uart_init()
{
    LL_USART_InitTypeDef uart_params = {
            .PrescalerValue=STM32_USART1_PRESCALER_VALUE,
            .BaudRate=STM32_USART1_BAUD_RATE,
            .DataWidth=STM32_USART1_DATA_WIDTH,
            .StopBits=STM32_USART1_STOP_BITS,
            .Parity=STM32_USART1_PARITY,
            .TransferDirection=STM32_USART1_TRANSFER_DIRECTION,
            .HardwareFlowControl=STM32_USART1_HARDWARE_FC,
            .OverSampling=STM32_USART1_OVER_SAMPLING
    };

#if STM32_ENABLE_USART1
    LL_USART_Init(USART1, &uart_params);

#if STM32_USART1_RS485
    LL_USART_EnableDEMode(USART1);
    LL_USART_SetDESignalPolarity(USART1, STM32_USART1_DE_POLARITY);
    LL_USART_SetDEAssertionTime(USART1, STM32_USART1_DE_ASSERT_TIME);
    LL_USART_SetDEDeassertionTime(USART1, STM32_USART1_DE_DEASSERT_TIME);

#endif // STM32_USART1_RS485

#if STM32_USART1_FIFO
    LL_USART_EnableFIFO(USART1);
#else
    LL_USART_DisableFIFO(USART1);
#endif // STM32_USART1_FIFO

#if STM32_USART1_ASYNC
    LL_USART_ConfigAsyncMode(USART1);
#endif // STM32_USART1_ASYNC

#if STM32_USART1_RX_ENABLE_DMA
    LL_USART_EnableDMAReq_RX(USART1);
#else
    LL_USART_DisableDMAReq_RX(USART1);

#endif // STM32_USART_RX_DMA

#if STM32_USART1_TX_DMA
    LL_USART_EnableDMAReq_TX(USART1);
#else
    LL_USART_DisableDMAReq_TX(USART1);

#endif // STM32_USART_TX_DMA

    LL_USART_Enable(USART1);
#ifndef SIMULATED
    while ((!(LL_USART_IsActiveFlag_TEACK(USART1))
            || (!(LL_USART_IsActiveFlag_REACK(USART1))))) {}
#endif

#if STM32_USART_RTO_ENABLE
    LL_USART_SetRxTimeout(USART1, STM32_RX_TIMEOUT);
    LL_USART_EnableRxTimeout(USART1);
    LL_USART_ClearFlag_RTO(USART1);

#ifndef SIMULATED
    while (LL_USART_IsActiveFlag_RTO(USART1));
#endif
    LL_USART_EnableIT_RTO(USART1);
#else

#endif //STM32_USART_RTO_ENABLE

    LL_USART_DisableIT_PE(USART1);
    LL_USART_DisableIT_ERROR(USART1);

#if STM32_USART_TC_ENABLE
    LL_USART_ClearFlag_TC(USART1);
#ifndef SIMULATED
    while (LL_USART_IsActiveFlag_TC(USART1));
#endif
    LL_USART_EnableIT_TC(USART1);
#else
    LL_USART_DisableIT_TC(USART1);
#endif //STM32_USART_TC_ENABLE

#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
    uart_params.PrescalerValue      = STM32_USART2_PRESCALER_VALUE;
    uart_params.BaudRate            = STM32_USART2_BAUD_RATE;
    uart_params.DataWidth           = STM32_USART2_DATA_WIDTH;
    uart_params.StopBits            = STM32_USART2_STOP_BITS;
    uart_params.Parity              = STM32_USART2_PARITY;
    uart_params.TransferDirection   = STM32_USART2_TRANSFER_DIRECTION;
    uart_params.HardwareFlowControl = STM32_USART2_HARDWARE_FC;
    uart_params.OverSampling        = STM32_USART2_OVER_SAMPLING;
    LL_USART_Init(USART2, &uart_params);

#if STM32_USART2_FIFO
    LL_USART_EnableFIFO(USART2);
#else
    LL_USART_DisableFIFO(USART2);
#endif // STM32_USART1_FIFO

#if STM32_USART2_ASYNC
    LL_USART_ConfigAsyncMode(USART2);
#endif // STM32_USART1_ASYNC

#endif // STM32_ENABLE_USART2
}
#if 0


static void
stm32_dma_transfer(uint16_t size)
{
    self.dma_pos_old = self.dma_pos_new;

    if (self.dma_pos_old + size > RX_BUFFER_SIZE) {
        uint16_t space = RX_BUFFER_SIZE - self.dma_pos_old;
        copy(self.rx_buffer + self.dma_pos_old, self.usart1_dma_buffer, space);
        self.dma_pos_old = 0;
        self.dma_pos_new = size - space;
        copy(self.rx_buffer, self.usart1_dma_buffer + space, self.dma_pos_new);
    } else {
        copy(self.rx_buffer + self.dma_pos_old, self.usart1_dma_buffer, size);
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
#endif
__INTERRUPT
USART1_IRQHandler()
{
    if (LL_USART_IsActiveFlag_TC(USART1)) {
#if STM32_USART1_RS485
        LL_GPIO_ResetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
#endif
        LL_USART_ClearFlag_TC(USART1);
    }
    if (LL_USART_IsActiveFlag_RXNE_RXFNE(USART1)) {
        return;
    } else if (LL_USART_IsActiveFlag_RTO(USART1)) {
#if 0
        if (DMA1_Channel1->CNDTR != STM32_USART_DMA_BUFFER_SIZE) {
            if (LL_DMA_IsActiveFlag_TC1(DMA1)) return;
            uint16_t size = STM32_USART_DMA_BUFFER_SIZE - DMA1_Channel1->CNDTR;
            stm32_dma_transfer(size);
            self.base.buffer_position += self.dma_pos_new;
        }
        self.rx_callback(0, self.base.buffer_position - self.rx_pos_old);
        LL_USART_ClearFlag_RTO(USART1);
        self.rx_pos_old = self.base.buffer_position;
#endif
    }
}