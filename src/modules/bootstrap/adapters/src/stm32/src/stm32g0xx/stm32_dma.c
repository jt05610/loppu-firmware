/**
  ******************************************************************************
  * @file   stm32_dma.c
  * @author Jonathan Taylor
  * @date   12/17/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <stdint.h>
#include <stdbool.h>
#include "stm32g0xx_ll_dma.h"
#include "adapters/stm32/config/default/dma_config.h"
#include "buffer/circular_buffer.h"
#include "stm32_dma.h"

typedef void (* dma_clear_flag_handler_t)(DMA_TypeDef * dma);


static inline void
stm32_dma_clear_flags(uint32_t channel)
{
    dma_clear_flag_handler_t tc_handlers[5][2] = {
            {LL_DMA_ClearFlag_HT1, LL_DMA_ClearFlag_TC1},
            {LL_DMA_ClearFlag_HT2, LL_DMA_ClearFlag_TC2},
            {LL_DMA_ClearFlag_HT3, LL_DMA_ClearFlag_TC3},
            {LL_DMA_ClearFlag_HT4, LL_DMA_ClearFlag_TC4},
            {LL_DMA_ClearFlag_HT5, LL_DMA_ClearFlag_TC5},
    };
    tc_handlers[channel][0](DMA1);
    tc_handlers[channel][1](DMA1);
}

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

#define __INIT_PERIPH(periph, mem_address)                                                  \
__DMA_SET_PERIPH_MEM(Address, periph, __GET(periph, PERIPH_ADDR), (uint32_t) mem_address);  \
LL_DMA_SetDataLength(DMA1, __GET(periph, CHANNEL), __GET(periph, BUFFER_SIZE));             \
LL_DMA_SetChannelPriorityLevel(DMA1, __GET(periph, CHANNEL), __GET(periph, PRIORITY));      \
LL_DMA_SetDataTransferDirection(DMA1, __GET(periph, CHANNEL), __GET(periph, TRANS_DIR));    \
LL_DMA_SetMode(DMA1, __GET(periph, CHANNEL), __GET(periph, CIRC_MODE));                     \
__DMA_SET_PERIPH_MEM(Size, periph, __GET(periph, PERIPH_SIZE), __GET(periph, MEM_SIZE));    \
__DMA_SET_PERIPH_MEM(IncMode, periph, __GET(periph, PERIPH_INC), __GET(periph, MEM_INC));   \
LL_DMA_SetPeriphRequest(DMA1, __GET(periph, CHANNEL),  __GET(periph, REQUEST));             \
stm32_dma_clear_flags(__GET(periph, CHANNEL));                                              \
__ENABLE(periph, HT);                                                                       \
__ENABLE(periph, TC)

#if STM32_USART1_RX_ENABLE_DMA
STATIC_CIRC_BUF(usart1_rx_dma_buffer, STM32_USART1_RX_DMA_BUFFER_SIZE);
#endif

#if STM32_USART2_RX_ENABLE_DMA
STATIC_CIRC_BUF(usart2_rx_dma_buffer, STM32_USART1_RX_DMA_BUFFER_SIZE);
#endif

void
stm32_dma_create(stm32_dma_mem_addr_t * params)
{
#if STM32_USART1_RX_ENABLE_DMA
    __INIT_PERIPH(_USART1_RX, params->usart1_rx);
#endif
#if STM32_USART2_RX_ENABLE_DMA
    __INIT_PERIPH(_USART2_RX, params->usart1_rx);
#endif
#if STM32_ADC_ENABLE_DMA
    __INIT_PERIPH(_ADC, params->adc);
#endif
}

void
stm32_dma_start_channel(uint8_t channel)
{
    LL_DMA_EnableChannel(DMA1, channel);
    while(!LL_DMA_IsEnabledChannel(DMA1, channel));
}

void
stm32_dma_stop_channel(uint8_t channel)
{
    LL_DMA_DisableChannel(DMA1, channel);
    while(LL_DMA_IsEnabledChannel(DMA1, channel));
}

void
stm32_dma_reset_channel(uint8_t channel)
{
    stm32_dma_stop_channel(channel);
}