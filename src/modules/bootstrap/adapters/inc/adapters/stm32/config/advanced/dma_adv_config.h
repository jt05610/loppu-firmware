/**
  ******************************************************************************
  * @file   dma_adv_config.h
  * @author Jonathan Taylor
  * @date   2/14/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_DMA_ADV_CONFIG_H
#define INJECTOR_DMA_ADV_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "adapters/stm32/config/default/adc_config.h"
#include "adapters/stm32/config/default/serial_config.h"

/**
 * @defgroup STM32G0xx_DMAAdvConfig DMA advanced config
 * @brief Advanced Configuration for STM32 DMA peripheral
 * @ingroup STM32G0xx_DMA
 * @{
 */


/**
 *******************************************************************************
 * @defgroup STM32G0xx_ADC_DMA ADC DMA config
 * @brief ADC direct memory access (DMA) configuration
 * @ingroup STM32G0xx_ADCConfig
 * @{
 */

/** @brief DMA memory size */
#define STM32_ADC_DMA_PERIPH_SIZE       LL_DMA_PDATAALIGN_HALFWORD

/** @brief DMA memory size */
#define STM32_ADC_DMA_MEM_SIZE          LL_DMA_MDATAALIGN_HALFWORD

/** @brief DMA peripheral increment mode */
#define STM32_ADC_DMA_PERIPH_INC        LL_DMA_PERIPH_NOINCREMENT

/** @brief DMA memory increment mode */
#define STM32_ADC_DMA_MEM_INC           LL_DMA_MEMORY_INCREMENT

/** @brief DMA request priority */
#define STM32_ADC_DMA_PRIORITY          LL_DMA_PRIORITY_HIGH

/** @brief DMA peripheral address */
#define STM32_ADC_DMA_PERIPH_ADDR       (uint32_t) &ADC1->DR

/** @brief DMA transfer direction for ADC*/
#define STM32_ADC_DMA_TRANS_DIR         LL_DMA_DIRECTION_PERIPH_TO_MEMORY

/** @brief DMA circular mode */
#define STM32_ADC_DMA_CIRC_MODE         LL_DMA_MODE_CIRCULAR

/** @brief DMA request */
#define STM32_ADC_DMA_REQUEST           LL_DMAMUX_REQ_ADC1

/** @brief Enable DMA half transfer complete interrupt generation */
#define STM32_ADC_DMA_ENABLE_HT         0

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_ADC_DMA_ENABLE_TC         0

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_ADC_DMA_ENABLE_TE         0

/** @brief DMA buffer size */
#define STM32_ADC_DMA_BUFFER_SIZE       STM32_ADC_BUFFER_SIZE

/** @} */

/**
 *******************************************************************************
 * @defgroup STM32G0xx_SerialDMAConfig Serial DMA config
 * @brief Serial direct memory access configuration
 * @ingroup STM32G0xx_SerialConfig
 * @{
 */


/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @defgroup STM32G0xx_USART1_DMAConfig USART1 DMA config
 * @brief USART1 DMA Config
 * @{
 */


/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @defgroup STM32G0xx_USART1_RX_DMAConfig RX Config
 * @brief USART1 RX DMA Config
 * @{
 */

/** @brief DMA memory size */
#define STM32_USART1_RX_DMA_PERIPH_SIZE       LL_DMA_PDATAALIGN_BYTE

/** @brief DMA memory size */
#define STM32_USART1_RX_DMA_MEM_SIZE          LL_DMA_MDATAALIGN_BYTE

/** @brief DMA peripheral increment mode */
#define STM32_USART1_RX_DMA_PERIPH_INC        LL_DMA_PERIPH_NOINCREMENT

/** @brief DMA memory increment mode */
#define STM32_USART1_RX_DMA_MEM_INC           LL_DMA_MEMORY_INCREMENT

/** @brief DMA request priority */
#define STM32_USART1_RX_DMA_PRIORITY          LL_DMA_PRIORITY_HIGH

/** @brief DMA peripheral address */
#define STM32_USART1_RX_DMA_PERIPH_ADDR       (uint32_t) &USART1->RDR

/** @brief DMA transfer direction */
#define STM32_USART1_RX_DMA_TRANS_DIR         LL_DMA_DIRECTION_PERIPH_TO_MEMORY

/** @brief DMA circular mode */
#define STM32_USART1_RX_DMA_CIRC_MODE         LL_DMA_MODE_NORMAL

/** @brief DMA request */
#define STM32_USART1_RX_DMA_REQUEST           LL_DMAMUX_REQ_USART1_RX

/** @brief Enable DMA half transfer complete interrupt generation */
#define STM32_USART1_RX_DMA_ENABLE_HT         0

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_USART1_RX_DMA_ENABLE_TC         1

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_USART1_RX_DMA_ENABLE_TE         0

/** @brief DMA buffer size */
#define STM32_USART1_RX_DMA_BUFFER_SIZE       STM32_USART1_RX_BUFFER_SIZE

/** @} */

/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @defgroup STM32G0xx_USART1_RX_DMAConfig RX Config
 * @brief USART1 RX DMA Config
 * @{
 */

/** @brief DMA memory size */
#define STM32_USART1_TX_DMA_PERIPH_SIZE       LL_DMA_PDATAALIGN_BYTE

/** @brief DMA memory size */
#define STM32_USART1_TX_DMA_MEM_SIZE          LL_DMA_MDATAALIGN_BYTE

/** @brief DMA peripheral increment mode */
#define STM32_USART1_TX_DMA_PERIPH_INC        LL_DMA_PERIPH_NOINCREMENT

/** @brief DMA memory increment mode */
#define STM32_USART1_TX_DMA_MEM_INC           LL_DMA_MEMORY_INCREMENT

/** @brief DMA request priority */
#define STM32_USART1_TX_DMA_PRIORITY          LL_DMA_PRIORITY_HIGH

/** @brief DMA peripheral address */
#define STM32_USART1_TX_DMA_PERIPH_ADDR       (uint32_t) &USART1->TDR

/** @brief DMA transfer direction */
#define STM32_USART1_TX_DMA_TRANS_DIR         LL_DMA_DIRECTION_MEMORY_TO_PERIPH

/** @brief DMA circular mode */
#define STM32_USART1_TX_DMA_CIRC_MODE         LL_DMA_MODE_NORMAL

/** @brief DMA request */
#define STM32_USART1_TX_DMA_REQUEST           LL_DMAMUX_REQ_USART1_TX

/** @brief Enable DMA half transfer complete interrupt generation */
#define STM32_USART1_TX_DMA_ENABLE_HT         0

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_USART1_TX_DMA_ENABLE_TC         0

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_USART1_TX_DMA_ENABLE_TE         0

/** @brief DMA buffer size */
#define STM32_USART1_TX_DMA_BUFFER_SIZE       0

/** @} */


/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @defgroup STM32G0xx_USART2_RX_DMAConfig RX Config
 * @brief USART2 RX DMA Config
 * @{
 */

/** @brief DMA memory size */
#define STM32_USART2_RX_DMA_PERIPH_SIZE       LL_DMA_PDATAALIGN_BYTE

/** @brief DMA memory size */
#define STM32_USART2_RX_DMA_MEM_SIZE          LL_DMA_MDATAALIGN_BYTE

/** @brief DMA peripheral increment mode */
#define STM32_USART2_RX_DMA_PERIPH_INC        LL_DMA_PERIPH_NOINCREMENT

/** @brief DMA memory increment mode */
#define STM32_USART2_RX_DMA_MEM_INC           LL_DMA_MEMORY_INCREMENT

/** @brief DMA request priority */
#define STM32_USART2_RX_DMA_PRIORITY          LL_DMA_PRIORITY_HIGH

/** @brief DMA peripheral address */
#define STM32_USART2_RX_DMA_PERIPH_ADDR       (uint32_t) &USART2->RDR

/** @brief DMA transfer direction */
#define STM32_USART2_RX_DMA_TRANS_DIR         LL_DMA_DIRECTION_PERIPH_TO_MEMORY

/** @brief DMA circular mode */
#define STM32_USART2_RX_DMA_CIRC_MODE         LL_DMA_MODE_NORMAL

/** @brief DMA request */
#define STM32_USART2_RX_DMA_REQUEST           LL_DMAMUX_REQ_USART2_RX

/** @brief Enable DMA half transfer complete interrupt generation */
#define STM32_USART2_RX_DMA_ENABLE_HT         0

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_USART2_RX_DMA_ENABLE_TC         1

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_USART2_RX_DMA_ENABLE_TE         0

/** @brief DMA buffer size */
#define STM32_USART2_RX_DMA_BUFFER_SIZE       0

/** @} */


/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @defgroup STM32G0xx_USART2_TX_DMAConfig RX Config
 * @brief USART2 RX DMA Config
 * @{
 */

/** @brief DMA memory size */
#define STM32_USART2_TX_DMA_PERIPH_SIZE       LL_DMA_PDATAALIGN_BYTE

/** @brief DMA memory size */
#define STM32_USART2_TX_DMA_MEM_SIZE          LL_DMA_MDATAALIGN_BYTE

/** @brief DMA peripheral increment mode */
#define STM32_USART2_TX_DMA_PERIPH_INC        LL_DMA_PERIPH_NOINCREMENT

/** @brief DMA memory increment mode */
#define STM32_USART2_TX_DMA_MEM_INC           LL_DMA_MEMORY_INCREMENT

/** @brief DMA request priority */
#define STM32_USART2_TX_DMA_PRIORITY          LL_DMA_PRIORITY_HIGH

/** @brief DMA peripheral address */
#define STM32_USART2_TX_DMA_PERIPH_ADDR       (uint32_t) &USART2->TDR

/** @brief DMA transfer direction */
#define STM32_USART2_TX_DMA_TRANS_DIR         LL_DMA_DIRECTION_MEMORY_TO_PERIPH

/** @brief DMA circular mode */
#define STM32_USART2_TX_DMA_CIRC_MODE         LL_DMA_MODE_NORMAL

/** @brief DMA request */
#define STM32_USART2_TX_DMA_REQUEST           LL_DMAMUX_REQ_USART2_TX

/** @brief Enable DMA half transfer complete interrupt generation */
#define STM32_USART2_TX_DMA_ENABLE_HT         0

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_USART2_TX_DMA_ENABLE_TC         0

/** @brief Enable DMA transfer complete interrupt generation */
#define STM32_USART2_TX_DMA_ENABLE_TE         0

/** @brief DMA buffer size */
#define STM32_USART2_TX_DMA_BUFFER_SIZE       0

/** @} */

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif //INJECTOR_DMA_ADV_CONFIG_H
