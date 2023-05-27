/**
  ******************************************************************************
  * @file   stm32_dma.h
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  STM32G0xx DMA implementation header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef STM32_DMA_H
#define STM32_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup STM32G0xx_DMA Direct memory access controller (DMA)
 * @ingroup STM32G0xx
 * @brief DMA is a bus master and system peripheral used to transfer between
 *        memory-mapped peripherals and/or memories.
 * @{
 */

#include <stdint.h>
#include "dma_config.h"
#include "adc_config.h"
#include "buffer/circular_buffer.h"

/** @brief Struct to pass memory address to dma */
typedef struct stm32_dma_mem_addr_t
{
#if STM32_ADC_ENABLE_DMA
    uint32_t adc;                      /**< @brief ADC buffer address */
#endif
#if STM32_ENABLE_USART1_RX_DMA
    uint8_t * usart1_rx_dma;            /**< @brief USART1 RX buffer address */
    circ_buf_t * usart1_rx_buffer;         /**< @brief USART1 RX circ buffer */
#endif
#if STM32_ENABLE_USART1_TX_DMA
    uint32_t usart1_tx;                /**< @brief USART1 TX buffer address */
#endif
#if STM32_ENABLE_USART2_RX_DMA
    uint32_t usart2_rx;                /**< @brief USART2 RX buffer address */
#endif
#if STM32_ENABLE_USART2_TX_DMA
    uint32_t usart2_tx;                /**< @brief USART2 TX buffer address */
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
 * @brief transfers dma to from memory address to configured peripheral addr
 * @param channel DMA channel
 * @param mem_addr memory address to transfer from
 * @param len number of bytes to transfer
 * @return 1 if successful else 0
 */
uint8_t stm32_dma_transfer(uint8_t channel, uint32_t mem_addr, uint16_t len);

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

uint16_t stm32_dma_channel_remaining(uint8_t channel);



void stm32_start_circ_buf_channel(uint8_t channel);

circ_buf_t * stm32_dma_circ_buf();
/** @} */

#ifdef __cplusplus
}
#endif

#endif // STM32_DMA_H
