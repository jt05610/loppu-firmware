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

#include <string.h>
#include "stm32_serial.h"

#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32_interrupts.h"
#include "stm32_dma.h"
#include "advanced/serial_adv_config.h"
#include "advanced/gpio_adv_config.h"
#include "advanced/dma_adv_config.h"
#include "default/dma_config.h"
#include "stm32_timer.h"


static struct
{
    serial_base_t base;
    bool new_data;

    void (* rto_cb)(void);

    uint8_t uart2_rx_buffer[STM32_USART2_RX_BUFFER_SIZE];
} self = {0};

STATIC_CIRC_BUF(uart1_rx, STM32_USART1_RX_BUFFER_SIZE);

static inline void uart_init();

static inline void open(void * instance);

static inline void close(void * instance);

static inline uint16_t available(void * instance);

static inline void clear(void * instance);

static inline uint16_t read(void * instance, uint8_t * bytes);

static inline void write(void * instance, uint8_t * bytes, uint16_t size);

static inline void
read_write(void * instance, uint8_t * bytes, uint16_t n_w, uint16_t n_r);

static inline void reg_rx_cb(void * instance, void(* cb)(void));

static inline uint8_t _putchar(void * instance, char a);

static serial_interface_t interface = {
        .open=open,
        .close=close,
        .available=available,
        .clear=clear,
        .read=read,
        .write=write,
        .read_write=read_write,
        .putchar=_putchar,
        .reg_rx_cb=reg_rx_cb
};

Serial
stm32_serial_create()
{
    self.base.vtable        = &interface;
    self.base.serial_buffer = &uart1_rx;
    self.new_data           = false;

#ifndef SIMULATED
    LL_GPIO_ResetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
#endif
    uart_init();
    return &self.base;
}

bool stm32_serial_new_data()
{
    return self.new_data;
}

circ_buf_t *
stm32_get_usart1_rx_circ_buffer()
{
    return &uart1_rx;
}

uint8_t *
stm32_get_usart2_rx_buffer()
{
    return self.uart2_rx_buffer;
}

static void
open(void * instance)
{
#if (STM32_ENABLE_USART1 & STM32_ENABLE_USART2)
#if STM32_ENABLE_USART1
    if ((USART_TypeDef *) instance == USART1) {
        stm32_start_circ_buf_channel(STM32_USART1_RX_DMA_CHANNEL);
#if STM32_ENABLE_USART1_RX_DMA
#endif // STM32_USART_RX_DMA

#if STM32_ENABLE_USART1_TX_DMA
        LL_DMA_EnableChannel(DMA1, STM32_USART1_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA
    }
#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
    if ((USART_TypeDef *) instance == USART2) {
#if STM32_ENABLE_USART2_RX_DMA
        LL_DMA_EnableChannel(DMA1, STM32_USART2_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_ENABLE_USART2_TX_DMA
        LL_DMA_EnableChannel(DMA1, STM32_USART2_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA
    }
#endif // STM32_ENABLE_USART2
#else
#if STM32_ENABLE_USART1
#if STM32_ENABLE_USART1_RX_DMA
    stm32_dma_start_channel(STM32_USART1_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2

#if STM32_ENABLE_USART2_RX_DMA
    LL_DMA_EnableChannel(DMA1, STM32_USART2_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_ENABLE_USART2_TX_DMA
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
    if ((USART_TypeDef *) instance == USART1) {
#if STM32_ENABLE_USART1_RX_DMA
        LL_DMA_DisableChannel(DMA1, STM32_USART1_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_ENABLE_USART1_TX_DMA
        LL_DMA_DisableChannel(DMA1, STM32_USART1_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA
    }
    if ((USART_TypeDef *) instance == USART2) {
#if STM32_ENABLE_USART2_RX_DMA
        LL_DMA_DisableChannel(DMA1, STM32_USART2_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_ENABLE_USART2_TX_DMA
        LL_DMA_DisableChannel(DMA1, STM32_USART2_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA
    }

#else
#if STM32_ENABLE_USART1
#if STM32_ENABLE_USART1_RX_DMA
    LL_DMA_DisableChannel(DMA1, STM32_USART1_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_ENABLE_USART1_TX_DMA
    LL_DMA_DisableChannel(DMA1, STM32_USART1_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA

#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2

#if STM32_ENABLE_USART2_RX_DMA
    LL_DMA_DisableChannel(DMA1, STM32_USART2_RX_DMA_CHANNEL);
#endif // STM32_USART_RX_DMA

#if STM32_ENABLE_USART2_TX_DMA
    LL_DMA_DisableChannel(DMA1, STM32_USART2_TX_DMA_CHANNEL);
#endif // STM32_USART_TX_DMA

#endif // STM32_ENABLE_USART2
#endif // STM32_ENABLE_USART1 & STM32_ENABLE_USART1
}

#define __BUFF_TRANSFER(src, dest, size)        \
size = circ_buf_waiting(src);                   \
for (uint16_t i = 0; i < size; i++)             \
    dest[i] = circ_buf_pop(src)

static uint16_t
read(void * instance, uint8_t * bytes)
{
    uint16_t size;
#if (STM32_ENABLE_USART1 & STM32_ENABLE_USART2)
    if ((USART_TypeDef *) instance == USART1) {
#if STM32_ENABLE_USART1_RX_DMA
        size = circ_buf_waiting(&uart1_rx);
        for (uint16_t i = 0; i < size; i++) {
            bytes[i] = circ_buf_pop(&uart1_rx);
        }

#else
        *bytes++ = LL_USART_ReceiveData8(USART1);
        size =  1;

#endif
    } else if ((USART_TypeDef *) instance == USART2) {
#if STM32_ENABLE_USART2_RX_DMA
        size = STM32_USART2_RX_DMA_BUFFER_SIZE - DMA1_Channel3->CNDTR;
        copy(bytes, self.uart2_rx_buffer, size);

#else
        bytes[0] = LL_USART_ReceiveData8(USART2);
        size = 1;
#endif
    } else {
        size = 0;
    }
#elif STM32_ENABLE_USART1
    (void) instance;
#if STM32_ENABLE_USART1_RX_DMA
    size = circ_buf_waiting(&uart1_rx);
    for (uint16_t i = 0; i < size; i++) {
        bytes[i] = circ_buf_pop(&uart1_rx);
    }

#else
    *bytes++ = LL_USART_ReceiveData8(USART1);
        size =  1;

#endif
#elif STM32_ENABLE_USART2
    (void) instance;
#if STM32_ENABLE_USART2_RX_DMA
        __BUFF_TRANSFER(&usart2_rx_circ, bytes, size);
#else
        *bytes++ = LL_USART_ReceiveData8(USART2);
        size = 1;
#endif
#else
        size = 0;
#endif
    return
            size;
}


#define _RE_HANDLER(port)  \
LL_GPIO_SetOutputPin(STM32_##port##_RE_PORT, STM32_##port##_RE_PIN);       \
while (!LL_GPIO_IsOutputPinSet(STM32_##port##_RE_PORT,STM32_##port##_RE_PIN))


static inline void
_handle_re(USART_TypeDef * inst)
{
    if (inst == USART1) {
#if STM32_USART1_RS485
        _RE_HANDLER(USART1);
#endif
    } else if (inst == USART2) {
#if STM32_USART2_RS485
        _RE_HANDLER(USART2);
#endif
    }
}

#define _TX_DMA_CHAN(port) \
STM32_##port##_TX_DMA_CHANNEL \

#define _GET_TX_DMA(port) \
port == USART1 ? _TX_DMA_CHAN(USART1) : _TX_DMA_CHAN(USART2)


static void
write(void * instance, uint8_t * bytes, uint16_t size)
{
#if STM32_USART1_RS485 || STM32_USART2_RS485
    _handle_re(instance);
#endif
    uint8_t channel = _GET_TX_DMA(instance);
    stm32_dma_transfer(channel, (uint32_t) bytes, size);
    while (stm32_dma_channel_remaining(channel));
}

static inline void
read_write(void * instance, uint8_t * bytes, uint16_t n_w, uint16_t n_r)
{
    while (stm32_dma_channel_remaining(STM32_USART2_RX_DMA_CHANNEL));
    stm32_dma_transfer(
            STM32_USART2_RX_DMA_CHANNEL, (uint32_t) self.uart2_rx_buffer,
            n_w + n_r);
    write(instance, bytes, n_w);
    if (n_r) {
        while (stm32_dma_channel_remaining(STM32_USART2_RX_DMA_CHANNEL));
        memcpy(bytes, self.uart2_rx_buffer + n_w, n_r);
    }
}

static uint8_t
_putchar(void * instance, char a)
{
#if STM32_ENABLE_USART1 & STM32_ENABLE_USART2
    if ((USART_TypeDef *) instance == USART1) {
#if STM32_USART1_RS485
        LL_GPIO_SetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);

#endif // STM32_USART1_RS485
        LL_USART_TransmitData8((USART_TypeDef *) instance, a);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF(
                (USART_TypeDef *) instance)) {}
    } else if ((USART_TypeDef *) instance == USART2) {
#if STM32_USART2_RS485
        LL_GPIO_SetOutputPin(STM32_USART2_RE_PORT, STM32_USART2_RE_PIN);
        while (!LL_GPIO_IsOutputPinSet(STM32_USART2_RE_PORT,
                                       STM32_USART2_RE_PIN)) {}
#endif // STM32_USART2_RS485

        LL_USART_TransmitData8(instance, (uint8_t) a);

        while (!LL_USART_IsActiveFlag_TXE_TXFNF((USART_TypeDef *) instance)) {}

        return (uint8_t) a;
    }

#elif STM32_ENABLE_USART1
    (void) instance;
#if STM32_USART1_RS485
    LL_GPIO_SetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
    while (!LL_GPIO_IsOutputPinSet(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN));

#endif // STM32_USART1_RS485
    LL_USART_TransmitData8((USART_TypeDef *) instance, a);
    while (!LL_USART_IsActiveFlag_TXE_TXFNF(
            (USART_TypeDef *) instance)) {}

#elif STM32_ENABLE_USART2
    (void) instance;
#if STM32_USART2_RS485
    LL_GPIO_SetOutputPin(STM32_USART2_RE_PORT, STM32_USART2_RE_PIN);
    while (!LL_GPIO_IsOutputPinSet(STM32_USART2_RE_PORT, STM32_USART2_RE_PIN));
#endif // STM32_USART2_RS485
#if !STM32_ENABLE_USART2_TX_DMA
    (void) instance;
    circ_buf_push(&usart1_tx_circ, (uint8_t) a);
#else
    LL_USART_TransmitData8(USART2, (uint8_t) a);
#endif
    return (uint8_t) a;
#else
    return a + 20;
#endif
    return 0;
}

#define __INIT_USART(params, inst)                           \
params->PrescalerValue=STM32_##inst##_PRESCALER_VALUE;       \
params->BaudRate=STM32_##inst##_BAUD_RATE;                   \
params->DataWidth=STM32_##inst##_DATA_WIDTH;                 \
params->StopBits=STM32_##inst##_STOP_BITS;                   \
params->Parity=STM32_##inst##_PARITY;                        \
params->TransferDirection=STM32_##inst##_TRANSFER_DIRECTION; \
params->HardwareFlowControl=STM32_##inst##_HARDWARE_FC;      \
params->OverSampling=STM32_##inst##_OVER_SAMPLING;           \
LL_USART_Init(inst, params);


#define __INIT_RS485(inst)                                              \
LL_USART_EnableDEMode(inst);                                            \
LL_USART_SetDESignalPolarity(USART1, STM32_##inst##_DE_POLARITY);       \
LL_USART_SetDEAssertionTime(USART1, STM32_##inst##_DE_ASSERT_TIME);     \
LL_USART_SetDEDeassertionTime(USART1, STM32_##inst##_DE_DEASSERT_TIME)

#define __SET_IT(inst, it)      \
LL_USART_ClearFlag_##it(inst);  \
STM32_##inst##_##it##_ENABLE    \
? LL_USART_EnableIT_##it(inst)  \
: LL_USART_DisableIT_##it(inst) \

#define __INIT_ONEWIRE(inst)            \
LL_USART_ConfigHalfDuplexMode(inst)         \


static void
uart1_init(LL_USART_InitTypeDef * uart_params)
{
    __INIT_USART(uart_params, USART1);
#if STM32_USART1_RS485
    __INIT_RS485(USART1);
#endif // STM32_USART1_RS485

#if STM32_USART1_FIFO
    LL_USART_EnableFIFO(USART1);
#else
    LL_USART_DisableFIFO(USART1);
#endif // STM32_USART1_FIFO

#if STM32_USART1_ASYNC
    LL_USART_ConfigAsyncMode(USART1);
#endif // STM32_USART1_ASYNC

#if STM32_ENABLE_USART1_RX_DMA
    LL_USART_EnableDMAReq_RX(USART1);
#else
    LL_USART_DisableDMAReq_RX(USART1);

#endif // STM32_USART_RX_DMA

#if STM32_ENABLE_USART1_TX_DMA
    LL_USART_EnableDMAReq_TX(USART1);
#else
    LL_USART_DisableDMAReq_TX(USART1);

#endif // STM32_USART_TX_DMA
    //LL_USART_DisableOverrunDetect(USART1);
#if STM32_USART1_RTO_ENABLE
    LL_USART_SetRxTimeout(USART1, STM32_USART1_RX_TIMEOUT);
    WRITE_REG(USART1->CR2, USART_CR2_RTOEN);
    LL_USART_EnableRxTimeout(USART1);
    WRITE_REG(USART1->ICR, USART_ICR_RTOCF);

#endif
    LL_USART_Enable(USART1);
    while ((!(LL_USART_IsActiveFlag_TEACK(USART1))) ||
           (!(LL_USART_IsActiveFlag_REACK(USART1)))) {
    }

    LL_USART_EnableIT_RXNE_RXFNE(USART1);
    __SET_IT(USART1, TC);
    __SET_IT(USART1, PE);
    __SET_IT(USART1, CM);
#if STM32_USART1_ERROR_ENABLE
    LL_USART_EnableIT_##it(inst);
#else
    LL_USART_DisableIT_ERROR(USART1);
#endif

}

#if STM32_ENABLE_USART2

static void
uart2_init(LL_USART_InitTypeDef * uart_params)
{
    __INIT_USART(uart_params, USART2);
#if STM32_USART2_RS485
    __INIT_RS485(USART2);
#endif // STM32_USART2_RS485

#if STM32_USART2_FIFO
    LL_USART_EnableFIFO(USART2);
#else
    LL_USART_DisableFIFO(USART2);
#endif // STM32_USART2_FIFO


#if STM32_ENABLE_USART2_ONEWIRE
    __INIT_ONEWIRE(USART2);
#endif // STM32_USART2_ASYNC

#if STM32_USART2_ASYNC
    LL_USART_ConfigAsyncMode(USART2);
#endif

#if STM32_ENABLE_USART2_RX_DMA
    LL_USART_EnableDMAReq_RX(USART2);
#else
    LL_USART_DisableDMAReq_RX(USART2);

#endif // STM32_USART_RX_DMA

#if STM32_ENABLE_USART2_TX_DMA
    LL_USART_EnableDMAReq_TX(USART2);
#else
    LL_USART_DisableDMAReq_TX(USART2);

#endif // STM32_USART_TX_DMA

    LL_USART_Enable(USART2);
    while ((!(LL_USART_IsActiveFlag_TEACK(USART2))) ||
           (!(LL_USART_IsActiveFlag_REACK(USART2)))) {
    }

    __SET_IT(USART2, PE);

#if STM32_USART2_ERROR_ENABLE
    LL_USART_EnableIT_##it(inst);
#else
    LL_USART_DisableIT_ERROR(USART2);
#endif

}

#endif

static inline void
byte_rx_cb()
{
    self.new_data = true;
    if (self.rto_cb) {
        stm32_dma_circ_buf()->head = STM32_USART1_RX_DMA_BUFFER_SIZE -
                                     stm32_dma_channel_remaining(
                                             STM32_USART1_RX_DMA_CHANNEL);
        circ_buf_transfer(&uart1_rx, stm32_dma_circ_buf());
        self.rto_cb();
    }
}

static void
uart_init()
{
    LL_USART_InitTypeDef uart_params;

#if STM32_ENABLE_USART1
    uart1_init(&uart_params);

    LL_USART_Enable(USART1);
    input_cap_irq(TIM3, STM32_USART1_BAUD_RATE*8, 150, byte_rx_cb);
#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
    uart2_init(&uart_params);
    LL_USART_Enable(USART2);
#endif // STM32_ENABLE_USART2

}

uint16_t
available(void * instance)
{
    if (instance == USART2) {
        return LL_USART_IsActiveFlag_RXNE_RXFNE(USART2);
    } else {
        if (!LL_USART_IsActiveFlag_RXNE_RXFNE(USART1)) {
            return self.new_data ? circ_buf_waiting(&uart1_rx) : 0;
        }
        return 0;
    }
}

static inline void
clear(void * instance)
{
    self.new_data  = false;
}

static inline void
reg_rx_cb(void * instance, void(* cb)(void))
{
    self.rto_cb = cb;
}

__INTERRUPT
USART1_IRQHandler()
{
    if (LL_USART_IsActiveFlag_TC(USART1)) {
#if STM32_USART1_RS485
        LL_GPIO_ResetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
#endif
        LL_USART_ClearFlag_TC(USART1);
    }

}

__INTERRUPT
USART2_IRQHandler()
{
}
