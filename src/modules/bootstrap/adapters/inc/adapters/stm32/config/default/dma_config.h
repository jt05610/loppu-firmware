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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#ifndef INJECTOR_DMA_CONFIG_H
#define INJECTOR_DMA_CONFIG_H

/**
 * @defgroup STM32G0xx_DMAConfig DMA config
 * @brief Configuration for STM32 DMA peripheral
 * @ingroup STM32G0xx_DMA
 * @{
 */
#include "stm32g0xx_ll_dma.h"
#include "serial_config.h"
#include "adc_config.h"

/**
 *******************************************************************************
 * @defgroup STM32G0xx_DMAChannels DMA Channel assignments
 * @brief Assignments for each channel
 * @note There may be overlap as long as only one overlapping channel is enabled
 */

#if STM32_ADC_ENABLE_DMA
/**
 * @brief DMA channel assignment for ADC
 * @ingroup STM32G0xx_ADCConfig
 */
#define STM32_ADC_DMA_CHANNEL           LL_DMA_CHANNEL_1
#endif

#if STM32_USART1_RX_ENABLE_DMA
/**
 * @brief DMA channel assignment for USART1 RX request
 * @ingroup STM32G0xx_SerialConfig
 */
#define STM32_USART1_RX_DMA_CHANNEL     LL_DMA_CHANNEL_2
#endif

#if STM32_USART2_RX_ENABLE_DMA
/**
 * @brief DMA channel assignment for USART2 RX request
 * @ingroup STM32G0xx_SerialConfig
 */
#define STM32_USART2_RX_DMA_CHANNEL     LL_DMA_CHANNEL_3
#endif

#if STM32_ADC_ENABLE_DMA
/**
 *******************************************************************************
 * @defgroup STM32G0xx_ADC_DMA ADC DMA config
 * @brief ADC direct memory access (DMA) configuration
 * @ingroup STM32G0xx_ADCConfig
 * @{
 */

/** @brief DMA memory size for ADC */
#define STM32_ADC_DMA_PERIPH_SIZE       LL_DMA_PDATAALIGN_HALFWORD

/** @brief DMA memory size for ADC */
#define STM32_ADC_DMA_MEM_SIZE          LL_DMA_MDATAALIGN_HALFWORD

/** @brief DMA peripheral increment mode for ADC */
#define STM32_ADC_DMA_PERIPH_INC        LL_DMA_PERIPH_NOINCREMENT

/** @brief DMA memory increment mode for ADC */
#define STM32_ADC_DMA_MEM_INC           LL_DMA_MEMORY_INCREMENT

/** @brief DMA request priority for ADC */
#define STM32_ADC_DMA_PRIORITY          LL_DMA_PRIORITY_HIGH

/** @brief DMA peripheral address for ADC */
#define STM32_ADC_DMA_PERIPH_ADDR       (uint32_t) &ADC1->DR

/** @brief DMA transfer direction for ADC*/
#define STM32_ADC_DMA_TRANS_DIR         LL_DMA_DIRECTION_PERIPH_TO_MEMORY

/** @brief DMA circular mode for ADC */
#define STM32_ADC_DMA_CIRC_MODE         LL_DMA_MODE_CIRCULAR

/** @brief DMA request for ADC */
#define STM32_ADC_DMA_REQUEST           LL_DMAMUX_REQ_ADC1

/** @brief Enable DMA half transfer complete interrupt generation for ADC */
#define STM32_ADC_DMA_ENABLE_HT         0

/** @brief Enable DMA transfer complete interrupt generation for ADC */
#define STM32_ADC_DMA_ENABLE_TC         0

/** @brief DMA buffer size */
#define STM32_ADC_DMA_BUFFER_SIZE    STM32_ADC_BUFFER_SIZE
/** @} */

#endif // STM32_ENABLE_ADC

/**
 * @defgroup STM32G0xx_SerialDMAConfig Serial DMA config
 * @brief Serial direct memory access configuration
 * @ingroup STM32G0xxSerialConfig
 * @{
 */

#define STM32_ENABLE_USART2_RX_DMA      1
#define STM32_ENABLE_USART2_TX_DMA      1

#if STM32_USART1_RX_ENABLE_DMA

/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART1_RX_DMA USART1 RX DMA config
 * @brief USART1_RX direct memory access (DMA) configuration
 * @ingroup STM32G0xx_USART1_RXConfig
 * @{
 */
/** @brief DMA channel to use for RX */
#define STM32_USART1_RX_DMA_PERIPH_SIZE LL_DMA_PDATAALIGN_BYTE
#define STM32_USART1_RX_DMA_MEM_SIZE    LL_DMA_MDATAALIGN_BYTE
#define STM32_USART1_RX_DMA_PERIPH_INC  LL_DMA_PERIPH_NOINCREMENT
#define STM32_USART1_RX_DMA_MEM_INC     LL_DMA_MEMORY_INCREMENT
#define STM32_USART1_RX_DMA_PRIORITY    LL_DMA_PRIORITY_HIGH
#define STM32_USART1_RX_DMA_PERIPH_ADDR (uint32_t) &USART1->RDR
#define STM32_USART1_RX_DMA_TRANS_DIR   LL_DMA_DIRECTION_PERIPH_TO_MEMORY
#define STM32_USART1_RX_DMA_CIRC_MODE   LL_DMA_MODE_NORMAL
#define STM32_USART1_RX_DMA_REQUEST     LL_DMAMUX_REQ_USART1_RX
#define STM32_USART1_RX_DMA_ENABLE_HT   0
#define STM32_USART1_RX_DMA_ENABLE_TC   1

/** @brief DMA buffer size */
#define STM32_USART1_RX_DMA_BUFFER_SIZE    8

/** @} */

#endif // STM32_USART1_RX_DMA

#if STM32_USART1_TX_DMA
/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART1_TX_DMA USART1 TX DMA config
 * @brief USART1_TX direct memory access (DMA) configuration
 * @ingroup STM32G0xx_USART1_TXConfig
 * @{
 */

#define STM32_USART1_TX_DMA_CHANNEL     LL_DMA_CHANNEL_2
#define STM32_USART1_TX_DMA_PERIPH_SIZE LL_DMA_PDATAALIGN_BYTE
#define STM32_USART1_TX_DMA_MEM_SIZE    LL_DMA_MDATAALIGN_BYTE
#define STM32_USART1_TX_DMA_PRIORITY    LL_DMA_PRIORITY_HIGH

/** @} */

#endif // STM32_USART1_TX_DMA

#if STM32_USART2_RX_ENABLE_DMA
/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART2_RX_DMA USART2 RX DMA config
 * @brief USART2_RX direct memory access (DMA) configuration
 * @ingroup STM32G0xx_USART2_RXConfig
 * @{
 */
#define STM32_USART2_RX_DMA_PERIPH_SIZE LL_DMA_PDATAALIGN_BYTE
#define STM32_USART2_RX_DMA_MEM_SIZE    LL_DMA_MDATAALIGN_BYTE
#define STM32_USART2_RX_DMA_PERIPH_INC  LL_DMA_PERIPH_NOINCREMENT
#define STM32_USART2_RX_DMA_MEM_INC     LL_DMA_MEMORY_INCREMENT
#define STM32_USART2_RX_DMA_PRIORITY    LL_DMA_PRIORITY_HIGH
#define STM32_USART2_RX_DMA_PERIPH_ADDR (uint32_t) &USART2->RDR
#define STM32_USART2_RX_DMA_TRANS_DIR   LL_DMA_DIRECTION_PERIPH_TO_MEMORY
#define STM32_USART2_RX_DMA_CIRC_MODE   LL_DMA_MODE_NORMAL
#define STM32_USART2_RX_DMA_REQUEST     LL_DMAMUX_REQ_USART2_RX
#define STM32_USART2_RX_DMA_ENABLE_HT   0
#define STM32_USART2_RX_DMA_ENABLE_TC   1
/** @brief DMA buffer size */
#define STM32_USART2_RX_DMA_BUFFER_SIZE    8
/** @} */

#endif // STM32_USART2_RX_DMA

#if STM32_USART2_TX_DMA
/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART2_TX_DMA USART2 TX DMA config
 * @brief USART2_TX direct memory access (DMA) configuration
 * @ingroup STM32G0xx_USART2_TXConfig
 * @{
 */

#define STM32_USART2_TX_DMA_CHANNEL     LL_DMA_CHANNEL_2
#define STM32_USART2_TX_DMA_PERIPH_SIZE LL_DMA_PDATAALIGN_BYTE
#define STM32_USART2_TX_DMA_MEM_SIZE    LL_DMA_MDATAALIGN_BYTE
#define STM32_USART2_TX_DMA_PRIORITY    LL_DMA_PRIORITY_HIGH

/** @} */

#endif // STM32_USART2_TX_DMA

/** @} */

#endif //INJECTOR_DMA_CONFIG_H

#pragma clang diagnostic pop