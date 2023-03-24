/**
  ******************************************************************************
  * @file   adc_config.h
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  Configuration macros for STM32G031xx ADC peripheral.
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
#ifndef STM32_ADC_CONFIG_H
#define STM32_ADC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @defgroup STM32G0xx_ADCConfig ADC config
 * @ingroup STM32G0xx_ADC
 * @ingroup STM32G0xx_DefaultConfig
 * @brief Default configuration for STM32G0xx
 * @{
 */

/**
 * @defgroup STM32G0xx_ADCConfig_Gen General ADC configuration
 * @brief Basic settings for ADC peripheral
 * @{
 */
#define STM32_ENABLE_ADC                1   /**< @brief Enable ADC peripheral */
#define STM32_ADC_BUFFER_SIZE           100 /**< @brief # of samples to store */
#define STM32_ADC_ENABLE_DMA            1   /**< @brief Enable DMA requests */

/** @} */

#ifdef __cplusplus
}
#endif

#endif //STM32_ADC_CONFIG_H


#pragma clang diagnostic pop