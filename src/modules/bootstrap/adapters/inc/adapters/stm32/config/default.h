/**
  ******************************************************************************
  * @file   default.h
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  Default configuration for stm32 peripherals.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_DEFAULT_H
#define INJECTOR_DEFAULT_H

#include "adapters/stm32/config/default/adc_config.h"
#include "adapters/stm32/config/default/rcc_config.h"
#include "adapters/stm32/config/default/serial_config.h"
#include "adapters/stm32/config/default/timer_config.h"
#include "adapters/stm32/config/default/gpio_config.h"

/**
 * @defgroup STM32G0xx_DefaultConfig Configuration
 * @ingroup STM32G0xx
 * @brief Configuration for STM32g031xx peripherals
 */

/**
 * @defgroup STM32G0xx_NVIC_Config
 * @brief Interrupt controller configuration
 * @ingroup STM32G0xx_DefaultConfig
 */



/**
 * @brief Enable USART peripheral
 * @ingroup STM32G0xx_ADCConfig
 */
#define STM32_ENABLE_SERIAL     1

/**
 * @brief Enable USART peripheral
 * @ingroup STM32G0xx_ADCConfig
 */
#define STM32_ENABLE_TIMER      1

/**
 * @brief Enable DMA peripheral
 * @ingroup STM32G0xx_DMAConfig
 */
#define STM32_ENABLE_DMA        1


#endif //INJECTOR_DEFAULT_H
