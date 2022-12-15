/**
  ******************************************************************************
  * @file   stm32_dma.h
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_STM32_DMA_H
#define INJECTOR_STM32_DMA_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32g0xx_ll_dma.h"

#define PERIPH_SIZE LL_DMA_PDATAALIGN_BYTE
#define MEM_SIZE LL_DMA_MDATAALIGN_BYTE
#define PRIORITY LL_DMA_PRIORITY_HIGH

typedef struct stm32_dma_params_t
{
    DMA_TypeDef * dma;
    uint32_t channel;
    uint32_t periph_address;
    uint32_t memory_address;
    uint32_t data_length;
    uint32_t transfer_direction;
    bool circular;
    uint32_t periph_request;
    bool enable_ht;
    bool enable_tc;
} stm32_dma_params_t;


typedef void (*dma_clear_flag_handler_t)(DMA_TypeDef * dma);

static inline void
stm32_dma_clear_flags(DMA_TypeDef *dma, uint32_t channel)
{
    dma_clear_flag_handler_t tc_handlers[5][2] = {
            {LL_DMA_ClearFlag_HT1, LL_DMA_ClearFlag_TC1},
            {LL_DMA_ClearFlag_HT2, LL_DMA_ClearFlag_TC2},
            {LL_DMA_ClearFlag_HT3, LL_DMA_ClearFlag_TC3},
            {LL_DMA_ClearFlag_HT4, LL_DMA_ClearFlag_TC4},
            {LL_DMA_ClearFlag_HT5, LL_DMA_ClearFlag_TC5},
    };
    tc_handlers[channel][0](dma);
    tc_handlers[channel][1](dma);
}

static inline void
stm32_dma_init(stm32_dma_params_t * p)
{
    LL_DMA_SetPeriphAddress(p->dma, p->channel, p->periph_address);
    LL_DMA_SetMemoryAddress(p->dma, p->channel, p->memory_address);
    LL_DMA_SetDataLength(p->dma, p->channel, p->data_length);
    LL_DMA_SetChannelPriorityLevel(p->dma, p->channel, PRIORITY);
    LL_DMA_SetDataTransferDirection(p->dma, p->channel, p->transfer_direction);
    if (p->circular)
    {
        LL_DMA_SetMode(p->dma, p->channel, LL_DMA_MODE_CIRCULAR);
    } else
    {
        LL_DMA_SetMode(p->dma, p->channel, LL_DMA_MODE_NORMAL);
    }
    LL_DMA_SetPeriphIncMode(p->dma, p->channel, LL_DMA_PERIPH_NOINCREMENT);
    LL_DMA_SetPeriphIncMode(p->dma, p->channel, LL_DMA_MEMORY_INCREMENT);
    LL_DMA_SetPeriphSize(p->dma, p->channel, PERIPH_SIZE);
    LL_DMA_SetMemorySize(p->dma, p->channel, MEM_SIZE);
    LL_DMA_SetPeriphRequest(p->dma, p->channel, p->periph_request);
    stm32_dma_clear_flags(p->dma, p->channel);
    if (p->enable_ht)
        LL_DMA_EnableIT_HT(p->dma, p->channel);
    else
        LL_DMA_DisableIT_HT(p->dma, p->channel);
    if (p->enable_tc)
        LL_DMA_EnableIT_TC(p->dma, p->channel);
    else
        LL_DMA_DisableIT_TC(p->dma, p->channel);
    LL_DMA_EnableChannel(p->dma, p->channel);
}

#endif //INJECTOR_STM32_DMA_H
