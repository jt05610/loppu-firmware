/**
  ******************************************************************************
  * @file   stm32_dma.c
  * @author Jonathan Taylor
  * @date   12/17/22
  * @brief  DMA implementation for STM32GG0xx
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <stdint.h>
#include "stm32g0xx_ll_dma.h"
#include "stm32_dma.h"
#include "stm32_interrupts.h"
#include "dma_config.h"
#include "nvic_config.h"
#include "serial_adv_config.h"
#include "dma_adv_config.h"
#include "isr_handler.h"

#define __DO(channel, func, flag) \
LL_DMA_##func##_##flag(DMA1, channel)

#define __GET(periph, item) STM32##periph##_DMA_##item

#define DMA_CLEAR_FLAG(flag, channel) LL_DMA_ClearFlag_##flag##channel

#define __ENABLE(periph, flag) \
__GET(periph, ENABLE_##flag)                        \
? __DO(__GET(periph, CHANNEL), EnableIT, flag)      \
: __DO(__GET(periph, CHANNEL), DisableIT, flag)

#define __DMA_SET_PERIPH_MEM(prop, periph, p_val, m_val)         \
LL_DMA_SetPeriph##prop(DMA1, __GET(periph, CHANNEL), p_val);     \
LL_DMA_SetMemory##prop(DMA1, __GET(periph, CHANNEL), m_val)

#define __INIT_PERIPH(periph, mem_address)                                      \
__DMA_SET_PERIPH_MEM(Address, periph, __GET(periph, PERIPH_ADDR), (uint32_t) mem_address);  \
LL_DMA_SetDataLength(DMA1, __GET(periph, CHANNEL), __GET(periph, BUFFER_SIZE));             \
LL_DMA_SetChannelPriorityLevel(DMA1, __GET(periph, CHANNEL), __GET(periph, PRIORITY));      \
LL_DMA_SetDataTransferDirection(DMA1, __GET(periph, CHANNEL), __GET(periph, TRANS_DIR));    \
LL_DMA_SetMode(DMA1, __GET(periph, CHANNEL), __GET(periph, CIRC_MODE));                     \
__DMA_SET_PERIPH_MEM(Size, periph, __GET(periph, PERIPH_SIZE), __GET(periph, MEM_SIZE));    \
__DMA_SET_PERIPH_MEM(IncMode, periph, __GET(periph, PERIPH_INC), __GET(periph, MEM_INC));   \
LL_DMA_SetPeriphRequest(DMA1, __GET(periph, CHANNEL),  __GET(periph, REQUEST));             \
__ENABLE(periph, HT);                                                                       \
__ENABLE(periph, TC);                                                                       \
__ENABLE(periph, TE)


#define __RESET_CHANNEL(periph)                                  \
    LL_DMA_DisableChannel(DMA1, __GET(periph, CHANNEL));         \
    LL_DMA_SetDataLength(                                        \
        DMA1, __GET(periph, CHANNEL), __GET(periph, BUFFER_SIZE) \
        );                                                       \
    LL_DMA_EnableChannel(DMA1, __GET(periph, CHANNEL))

#define __LL_DMA_CHANNEL(channel) LL_DMA_CHANNEL_##channel

#define DMA_CHANNEL(periph) __LL_DMA_CHANNEL(STM32_##periph##_DMA_CHANNEL)

#define __HNDLR(flag, channel)  dma_##flag##channel##_hndl

static struct
{
    circ_buf_t * dest_buf;
} self = {};

STATIC_CIRC_BUF(uart1_dma, STM32_USART1_RX_DMA_BUFFER_SIZE);

void
stm32_start_circ_buf_channel(uint8_t channel)
{
    LL_DMA_DisableChannel(DMA1, channel);
    LL_DMA_SetDataLength(DMA1, channel, STM32_USART1_RX_DMA_BUFFER_SIZE);
    LL_DMA_SetMemoryAddress(DMA1, channel, (uint32_t) uart1_dma_buffer);
    LL_DMA_EnableChannel(DMA1, channel);
}

circ_buf_t * stm32_dma_circ_buf()
{
    return &uart1_dma;
}

void
stm32_dma_create(stm32_dma_mem_addr_t * params)
{
#if STM32_ADC_ENABLE_DMA
    __INIT_PERIPH(_ADC, params->adc);
#endif
#if STM32_ENABLE_USART1_RX_DMA
    self.dest_buf = params->usart1_rx_buffer;
    __INIT_PERIPH(_USART1_RX, uart1_dma_buffer);
    stm32_start_circ_buf_channel(STM32_USART1_RX_DMA_CHANNEL);
#endif
#if STM32_ENABLE_USART1_TX_DMA
    __INIT_PERIPH(_USART1_TX, params->usart1_tx);
#endif
#if STM32_ENABLE_USART2_RX_DMA
    __INIT_PERIPH(_USART2_RX, params->usart2_rx);
#endif
#if STM32_ENABLE_USART2_TX_DMA
    __INIT_PERIPH(_USART2_TX, 0);
#endif
}

void
stm32_dma_start_channel(uint8_t channel)
{
    LL_DMA_EnableChannel(DMA1, channel);
    while (!LL_DMA_IsEnabledChannel(DMA1, channel));
}

void
stm32_dma_stop_channel(uint8_t channel)
{
    LL_DMA_DisableChannel(DMA1, channel);
    while (LL_DMA_IsEnabledChannel(DMA1, channel));
}

uint16_t
stm32_dma_channel_remaining(uint8_t channel)
{
    return LL_DMA_GetDataLength(DMA1, channel);
}

uint8_t
stm32_dma_transfer(uint8_t channel, uint32_t mem_addr, uint16_t len)
{
    uint8_t started = 0;
    if (len) {
        LL_DMA_DisableChannel(DMA1, channel);
        while (LL_DMA_IsEnabledChannel(DMA1, channel));
        LL_DMA_SetDataLength(DMA1, channel, len);
        LL_DMA_SetMemoryAddress(DMA1, channel, mem_addr);
        LL_DMA_EnableChannel(DMA1, channel);
        while (!LL_DMA_IsEnabledChannel(DMA1, channel));
        started = 1;
    }
    return started;
}

#if STM32_ENABLE_DMA1_Channel1_IRQn

__INTERRUPT
DMA1_Channel1_IRQHandler()
{
    if (LL_DMA_IsActiveFlag_TC1(DMA1)) {
        uart1_dma.head = STM32_USART1_RX_DMA_BUFFER_SIZE;
        circ_buf_transfer(self.dest_buf, &uart1_dma);
        uart1_dma.empty = true;
        LL_DMA_ClearFlag_TC1(DMA1);
    } if (LL_DMA_IsActiveFlag_HT1(DMA1)) {
        uart1_dma.head = STM32_USART1_RX_DMA_BUFFER_SIZE / 2;
        LL_DMA_ClearFlag_HT1(DMA1);
        uart1_dma.empty = false;
    }
}

#endif

#if STM32_ENABLE_DMA1_Channel2_3_IRQn

__INTERRUPT
DMA1_Channel2_3_IRQHandler()
{

__INTERRUPT DMA_ISR_HANDLER(TC, 2)
{
    LL_DMA_DisableChannel(DMA1, STM32_USART1_TX_DMA_CHANNEL);
    LL_DMA_SetDataLength(
            DMA1, STM32_USART1_TX_DMA_CHANNEL, STM32_USART1_TX_DMA_BUFFER_SIZE
    );
}

DMA_ISR_HANDLER(TC, 3)
{
    LL_DMA_ClearFlag_TC3(DMA1);
    __RESET_CHANNEL(_USART2_RX);
}

}

#endif

#if STM32_ENABLE_DMA1_Ch4_5_DMAMUX1_OVR_IRQn
__INTERRUPT
DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler()
{

}
#endif
