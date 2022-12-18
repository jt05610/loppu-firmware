/**
  ******************************************************************************
  * @file   stm32_adc.h
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  STM32G0xx ADC peripheral header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef STM32_ADC_H
#define STM32_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "analog.h"

/**
 * @defgroup STM32G0xx_ADC Analog-to-digital-converter (ADC)
 * @brief ADC implementation for STM32G031xx
 * @ingroup STM32G0xx
 * @{
 */

/**
 * @brief Initializes ADC
 * @return Initialized pointer to initialized @ref analog_t
 */
Analog stm32_adc_create();

/**
 * @brief Gets ADC buffer
 * @return Adc buffer
 */
volatile uint16_t * stm32_adc_get_buffer();

/** @} */

#ifdef __cplusplus
}
#endif

#endif //STM32_ADC_H
