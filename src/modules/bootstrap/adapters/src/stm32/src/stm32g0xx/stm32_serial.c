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
#include "stm32g0xx_ll_dma.h"
#include "default/dma_config.h"
#include "stm32_interrupts.h"
#include "stm32_dma.h"

static struct
{
    serial_base_t base;
    bool new_data;
} self = {0};

static inline void uart_init();

static inline void open(void * instance);

static inline void close(void * instance);

static inline uint16_t available(void * instance);

static inline void clear(void * instance);

static inline uint16_t read(void * instance, uint8_t * bytes);

static inline void write(void * instance, uint8_t * bytes, uint16_t size);

static inline uint8_t _putchar(void * instance, char a);

static serial_interface_t interface = {
        .open=open,
        .close=close,
        .available=available,
        .clear=clear,
        .read=read,
        .write=write,
        .putchar=_putchar
};

#if STM32_ENABLE_USART1_RX_DMA
STATIC_CIRC_BUF(usart1_rx_circ, STM32_USART1_RX_BUFFER_SIZE);
STATIC_CIRC_BUF(usart1_rx_dma_circ, STM32_USART1_RX_DMA_BUFFER_SIZE);

circ_buf_t *
stm32_get_usart1_rx_buffer()
{
    return &usart1_rx_dma_circ;
}

circ_buf_t *
stm32_get_usart1_rx_circ_buffer()
{
    return &usart1_rx_circ;
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

static void
open(void * instance)
{
#if (STM32_ENABLE_USART1 & STM32_ENABLE_USART2)
#if STM32_ENABLE_USART1
    if ((USART_TypeDef *) instance == USART1) {
#if STM32_ENABLE_USART1_RX_DMA
        LL_DMA_EnableChannel(DMA1, STM32_USART1_RX_DMA_CHANNEL);
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
#if (STM32_ENABLE_USART1 & STM32_ENABLE_USART2)
    if ((USART_TypeDef *) instance == USART1) {
#if STM32_ENABLE_USART1_RX_DMA
        uint16_t size;
        __BUFF_TRANSFER(&usart1_rx_circ, bytes, size);
        return size;
#else
        LL_USART_ReceiveData8(USART1);
#endif
    } else if ((USART_TypeDef *) instance == USART2) {
#if STM32_ENABLE_USART2_RX_DMA
        uint16_t size;
        __BUFF_TRANSFER(&usart2_rx_circ, bytes, size);
#else
        *bytes++ = LL_USART_ReceiveData8(USART2);
        return 1;
#endif
    } else {
        return 0;
    }
#elif STM32_ENABLE_USART1
    (void) instance;
#if STM32_ENABLE_USART1_RX_DMA
    if (self.new_data & !circ_buf_waiting(&usart1_rx_circ)) {
        /* if we have new data but dma hasn't processed yet */
        if (!circ_buf_waiting(&usart1_rx_circ)) {
            /* if there isn't data in the dma buffer yet */
            uint16_t initial        = DMA1_Channel1->CNDTR;
            uint16_t retries        = 10000;
            while (1) {
                if (DMA1_Channel1->CNDTR == initial) {
                    retries--;
                    if (retries == 0) {
                        usart1_rx_dma_circ.empty = false;
                        break;
                    }
                } else {
                    initial = DMA1_Channel1->CNDTR;
                }
            }
            usart1_rx_dma_circ.head =
                    STM32_USART1_RX_DMA_BUFFER_SIZE - DMA1_Channel1->CNDTR;
        }
        uint16_t size = circ_buf_waiting(&usart1_rx_dma_circ);
        if (size) {
            circ_buf_transfer(&usart1_rx_circ, &usart1_rx_dma_circ);
        }
    }
    uint16_t size = circ_buf_waiting(&usart1_rx_circ);
    if (size) {
        __BUFF_TRANSFER(&usart1_rx_circ, bytes, size);
    } else {
        size = 0;
    }
#else
    *bytes++ = LL_USART_ReceiveData8(USART1);
    return 1;
#endif
#elif STM32_ENABLE_USART2
    (void) instance;
#if STM32_ENABLE_USART2_RX_DMA
        uint16_t size;
        __BUFF_TRANSFER(&usart2_rx_circ, bytes, size);
#else
        *bytes++ = LL_USART_ReceiveData8(USART2);
        return 1;
#endif
#else
        return 0;
#endif
    return size;
}

static void
write(void * instance, uint8_t * bytes, uint16_t size)
{
#if STM32_ENABLE_USART1 & STM32_ENABLE_USART2

    if ((USART_TypeDef *) instance == USART1) {
#if STM32_USART1_RS485
        LL_GPIO_SetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
        while (!LL_GPIO_IsOutputPinSet(STM32_USART1_RE_PORT,
                                       STM32_USART1_RE_PIN)) {}
#endif // STM32_USART1_RS485
#if STM32_ENABLE_USART1_TX_DMA
        uint8_t * ptr = bytes;
        while (size--) {
            circ_buf_push(&usart1_tx_circ, *ptr++);
        }
#else
        for (uint16_t i = 0; i < size; i++) {
        LL_USART_TransmitData8((USART_TypeDef *) instance, bytes[i]);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF((USART_TypeDef *) instance));
    }
#endif
    } else if ((USART_TypeDef *) instance == USART2) {

#if STM32_USART2_RS485
        LL_GPIO_SetOutputPin(STM32_USART2_RE_PORT, STM32_USART2_RE_PIN);
        while (!LL_GPIO_IsOutputPinSet(STM32_USART2_RE_PORT,
                                       STM32_USART2_RE_PIN)) {}
#endif // STM32_USART2_RS485

#if STM32_ENABLE_USART2_TX_DMA
        uint8_t *ptr = bytes;
        while (size --)
            circ_buf_push(&usart2_tx_circ, *ptr++);
#else
        for (uint16_t i = 0; i < size; i++) {
            LL_USART_TransmitData8(USART2, bytes[i]);
            while (!LL_USART_IsActiveFlag_TXE_TXFNF(USART2));
        }
#endif
    }
#elif STM32_ENABLE_USART1
    (void) instance;
#if STM32_USART1_RS485
    LL_GPIO_SetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
    while (!LL_GPIO_IsOutputPinSet(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN));
#endif // STM32_USART1_RS485
#if STM32_ENABLE_USART1_TX_DMA
    LL_DMA_SetDataLength(DMA1, STM32_USART1_TX_DMA_CHANNEL, size);
    LL_DMA_SetMemoryAddress(DMA1, STM32_USART1_TX_DMA_CHANNEL, (uint32_t) bytes);
    stm32_dma_start_channel(STM32_USART1_TX_DMA_CHANNEL);
#else
    for (uint16_t i = 0; i < size; i++) {
        LL_USART_TransmitData8((USART_TypeDef *) instance, bytes[i]);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF((USART_TypeDef *) instance));
    }
#endif
#elif STM32_ENABLE_USART2
    (void) instance;
#if STM32_USART2_RS485
    LL_GPIO_SetOutputPin(STM32_USART2_RE_PORT, STM32_USART2_RE_PIN);
    while (!LL_GPIO_IsOutputPinSet(STM32_USART2_RE_PORT, STM32_USART2_RE_PIN));
#endif // STM32_USART2_RS485
#if STM32_ENABLE_USART2_TX_DMA
    uint8_t *ptr = bytes;
    while (size --)
        circ_buf_push(&usart2_tx_circ, *ptr++);
#else
    for (uint16_t i = 0; i < size; i++) {
        LL_USART_TransmitData8(USART2, bytes[i]);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF(USART2);
    }
#endif
#endif

}

static uint8_t
_putchar(void * instance, char a)
{
#if STM32_ENABLE_USART1 & STM32_ENABLE_USART2
    if ((USART_TypeDef *) instance == USART1) {
#if STM32_USART1_RS485
        LL_GPIO_SetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
        while (!LL_GPIO_IsOutputPinSet(STM32_USART1_RE_PORT,
                                       STM32_USART1_RE_PIN)) {}
#endif // STM32_USART1_RS485
#if STM32_ENABLE_USART1_TX_DMA
        circ_buf_push(&usart1_tx_circ, (uint8_t) a);
        return (uint8_t) a;
#else
        LL_USART_TransmitData8((USART_TypeDef *) instance, bytes[i]);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF((USART_TypeDef *) instance));
    }
#endif // STM32_ENABLE_USART1_TX_DMA
    } else if ((USART_TypeDef *) instance == USART2) {
#if STM32_USART2_RS485
        LL_GPIO_SetOutputPin(STM32_USART2_RE_PORT, STM32_USART2_RE_PIN);
        while (!LL_GPIO_IsOutputPinSet(STM32_USART2_RE_PORT,
                                       STM32_USART2_RE_PIN)) {}
#endif // STM32_USART2_RS485
#if STM32_ENABLE_USART2_TX_DMA
        circ_buf_push(&usart2_tx_circ, (uint8_t) a);
#else
        LL_USART_TransmitData8(USART2, (uint8_t) a);
        while (!LL_USART_IsActiveFlag_TXE_TXFNF((USART_TypeDef *) instance));
        return (uint8_t) a;
#endif
    }

#elif STM32_ENABLE_USART1
    (void) instance;
#if STM32_USART1_RS485
    LL_GPIO_SetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
    while (!LL_GPIO_IsOutputPinSet(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN));
#endif // STM32_USART1_RS485
#if STM32_ENABLE_USART1_TX_DMA
    (void) instance;
    circ_buf_push(&usart1_tx_circ, (uint8_t) a);
#else
    LL_USART_TransmitData8(USART1, (uint8_t) a);
    while (!LL_USART_IsActiveFlag_TXE_TXFNF(USART1));
    return a;
#endif
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
    LL_USART_Enable(USART1);
    while ((!(LL_USART_IsActiveFlag_TEACK(USART1))) ||
           (!(LL_USART_IsActiveFlag_REACK(USART1)))) {
    }
#if STM32_USART1_RTO_ENABLE
    LL_USART_SetRxTimeout(USART1, STM32_USART1_RX_TIMEOUT);
    LL_USART_EnableRxTimeout(USART1);
#endif
    LL_USART_ConfigNodeAddress(USART1, LL_USART_ADDRESS_DETECT_7B, 0x0A);
    __SET_IT(USART1, RTO);
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

#if STM32_USART2_ASYNC
    LL_USART_ConfigAsyncMode(USART2);
#endif // STM32_USART2_ASYNC

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
    __SET_IT(USART2, TC);
    __SET_IT(USART2, RTO);
    __SET_IT(USART2, PE);
#if STM32_USART2_ERROR_ENABLE
    LL_USART_EnableIT_##it(inst);
#else
    LL_USART_DisableIT_ERROR(USART2);
#endif
}
#endif

static void
uart_init()
{
    LL_USART_InitTypeDef uart_params;

#if STM32_ENABLE_USART1
    uart1_init(&uart_params);
#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
    uart2_init(&uart_params);
#endif // STM32_ENABLE_USART2
    self.new_data = false;
}

uint16_t
available(void * instance)
{
    if (!self.new_data) {
        usart1_rx_dma_circ.head = STM32_USART1_RX_DMA_BUFFER_SIZE - LL_DMA_GetDataLength(DMA1, STM32_USART1_RX_DMA_CHANNEL);
        usart1_rx_dma_circ.empty = usart1_rx_dma_circ.head == usart1_rx_dma_circ.tail;
        self.new_data = circ_buf_waiting(&usart1_rx_dma_circ);
    }
    return self.new_data;
}

static inline void
clear(void * instance)
{
    self.new_data = false;
}

__INTERRUPT
USART1_IRQHandler()
{
    if (LL_USART_IsActiveFlag_TC(USART1)) {
#if STM32_USART1_RS485
        LL_GPIO_ResetOutputPin(STM32_USART1_RE_PORT, STM32_USART1_RE_PIN);
#endif
        LL_USART_ClearFlag_TC(USART1);
    } else if (LL_USART_IsActiveFlag_RTO(USART1)) {
        while (!LL_USART_IsActiveFlag_REACK(USART1));

        self.new_data = true;
        LL_USART_ClearFlag_RTO(USART1);
    }
}