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

/**
 * @defgroup STM32G0xx_DMA Direct memory access controller (DMA)
 * @ingroup STM32G0xx
 * @brief DMA is a bus master and system peripheral used to transfer between
 *        memory-mapped peripherals and/or memories.
 * @{
 */

#include <stdint.h>

/** @brief Struct to pass memory address to dma */
typedef struct stm32_dma_mem_addr_t {
#if STM32_USART1_RX_ENABLE_DMA
    uint32_t usart1_rx;                /**< @brief USART1 RX buffer address */
#endif
#if STM32_USART2_RX_ENABLE_DMA
    uint32_t usart2_rx;                /**< @brief USART2 RX buffer address */
#endif
#if STM32_ADC_ENABLE_DMA
    uint32_t adc;                      /**< @brief ADC buffer address */
#endif
} stm32_dma_mem_addr_t;

/**
 * @brief initializes DMA
 * @see dma_config.h
 */
void stm32_dma_create(stm32_dma_mem_addr_t * params);

/**
 * @brief Enables DMA channel
 * @param channel DMA channel
 */
void stm32_dma_start_channel(uint8_t channel);

/**
 * @brief Stops DMA channel
 * @param channel DMA channel
 */
void stm32_dma_stop_channel(uint8_t channel);

/**
 * @brief Resets DMA channel
 * @param channel DMA channel
 */
void stm32_dma_reset_channel(uint8_t channel);

/** @} */

#endif //INJECTOR_STM32_DMA_H
