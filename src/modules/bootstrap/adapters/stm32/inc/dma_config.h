/**
  ******************************************************************************
  * @file   dma_config.h
  * @author Jonathan Taylor
  * @date   12/17/22
  * @brief  Configuration macros for STM32G0xx DMA.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DMA_CONFIG_H
#define DMA_CONFIG_H
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @defgroup STM32G0xx_DMAConfig DMA config
 * @brief Configuration for STM32 DMA peripheral
 * @ingroup STM32G0xx_DMA
 * @{
 */
#include "stm32g0xx_ll_dma.h"
#include "serial_config.h"


#define STM32_ENABLE_DMA                1   /**< @brief Enable DMA */
#define STM32_ENABLE_USART1_RX_DMA      1   /**< @brief Enable USART1 RX DMA */
#define STM32_ENABLE_USART1_TX_DMA      1   /**< @brief Enable USART1 TX DMA */
#define STM32_ENABLE_USART2_RX_DMA      1   /**< @brief Enable USART2 RX DMA */
#define STM32_ENABLE_USART2_TX_DMA      1   /**< @brief Enable USART2 TX DMA */

/**
 *******************************************************************************
 * @defgroup STM32G0xx_DMAChannels DMA Channel assignments
 * @brief Assignments for each channel
 * @note There may be overlap as long as only one overlapping channel is enabled
 */

/**
 * @brief DMA channel assignment for ADC
 * @ingroup STM32G0xx_ADCConfig
 */
#define STM32_ADC_DMA_CHANNEL           LL_DMA_CHANNEL_5

/**
 * @brief DMA channel assignment for USART1 RX request
 * @ingroup STM32G0xx_SerialConfig
 */
#define STM32_USART1_RX_DMA_CHANNEL     LL_DMA_CHANNEL_1

/**
 * @brief DMA channel assignment for USART1 TX request
 * @ingroup STM32G0xx_SerialConfig
 */
#define STM32_USART1_TX_DMA_CHANNEL     LL_DMA_CHANNEL_2

/**
 * @brief DMA channel assignment for USART2 RX request
 * @ingroup STM32G0xx_SerialConfig
 */
#define STM32_USART2_RX_DMA_CHANNEL     LL_DMA_CHANNEL_3

/**
 * @brief DMA channel assignment for USART2 TX request
 * @ingroup STM32G0xx_SerialConfig
 */
#define STM32_USART2_TX_DMA_CHANNEL     LL_DMA_CHANNEL_4


/** @} */

/** @} */


#ifdef __cplusplus
}
#endif

#endif // DMA_CONFIG_H

#pragma clang diagnostic pop
