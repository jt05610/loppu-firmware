/**
  ******************************************************************************
  * @file   analog.h
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

#ifndef INJECTOR_ANALOG_H
#define INJECTOR_ANALOG_H

/**
 * @defgroup STM32G0xx_ADCConfig_Gen General ADC configuration
 * @brief Basic settings for ADC peripheral
 * @{
 */
#define STM32_ENABLE_ADC                0   /**< @brief Enable ADC peripheral */
#define STM32_ADC_BUFFER_SIZE           100 /**< @brief # of samples to store */
#define STM32_ADC_ENABLE_DMA            1   /**< @brief Enable DMA requests */

#endif //INJECTOR_ANALOG_H
