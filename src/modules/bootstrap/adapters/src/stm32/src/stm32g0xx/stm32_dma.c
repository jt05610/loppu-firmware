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
#include "default/dma_config.h"
#include "default/nvic_config.h"

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

#define __INIT_PERIPH(periph, mem_address, flag_track)                                      \
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

void
stm32_dma_create(stm32_dma_mem_addr_t * params)
{
#if STM32_ADC_ENABLE_DMA
    __INIT_PERIPH(_ADC, params->adc, nvic_tracker);
#endif
#if STM32_ENABLE_USART1_RX_DMA
    __INIT_PERIPH(_USART1_RX, params->usart1_rx, nvic_tracker);
#endif
#if STM32_ENABLE_USART1_TX_DMA
    __INIT_PERIPH(_USART1_TX, params->usart1_tx, nvic_tracker);
#endif
#if STM32_ENABLE_USART2_RX_DMA
    __INIT_PERIPH(_USART2_RX, params->usart2_rx, nvic_tracker);
#endif
#if STM32_ENABLE_USART2_TX_DMA
    __INIT_PERIPH(_USART2_TX, params->usart2_tx, nvic_tracker);
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

void
stm32_dma_reset_channel(uint8_t channel)
{
    stm32_dma_stop_channel(channel);
    stm32_dma_start_channel(channel);
}

#define __HANDLE(flag, channel) if(LL_DMA_IsActiveFlag_##flag##channel)
#define __CLEAR(flag, channel) LL_DMA_ClearFlag_##flag##channel
#define __CLEAR_FLAGS(channel)  __CLEAR(TC, channel); __CLEAR(TE, channel)

__INTERRUPT
DMA1_Channel1_IRQHandler()
{
#if STM32_ENABLE_DMA1_Channel1_IRQn
    __HANDLE(HT, 1) {

        __CLEAR(HT, 1);
    }
    __HANDLE(TC, 1) {

        __CLEAR(TC, 1);
    }
    __HANDLE(TE, 1) {

        __CLEAR(TE, 1);
    }
#endif
}

__INTERRUPT
DMA1_Channel2_3_IRQHandler()
{
#if STM32_ENABLE_DMA1_Channel2_3_IRQn
    __HANDLE(HT, 2) {

        __CLEAR(HT, 2);
    }
    __HANDLE(TC, 2) {

        __CLEAR(TC, 2);
    }
    __HANDLE(TE, 2) {

        __CLEAR(TE, 2);
    }
    __HANDLE(HT, 3) {

        __CLEAR(HT, 3);
    }
    __HANDLE(TC, 3) {

        __CLEAR(TC, 3);
    }
    __HANDLE(TE, 3) {

        __CLEAR(TE, 3);
    }
#endif
}

__INTERRUPT
DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler()
{
#if STM32_ENABLE_DMA1_Ch4_5_DMAMUX1_OVR_IRQn
    __HANDLE(HT, 4) {

        __CLEAR(HT, 4);
    }
    __HANDLE(TC, 4) {

        __CLEAR(TC, 4);
    }
    __HANDLE(TE, 4) {

        __CLEAR(TE, 4);
    }
    __HANDLE(HT, 5) {

        __CLEAR(HT, 5);
    }
    __HANDLE(TC, 5) {

        __CLEAR(TC, 5);
    }
    __HANDLE(TE, 5) {

        __CLEAR(TE, 5);
    }
#endif
}
