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


/**
 * @defgroup STM32G0xx_DefaultConfig Configuration
 * @ingroup STM32G0xx
 * @brief Configuration for STM32g031xx peripherals
 * @{
 */

#include "adapters/stm32/config/default/adc_config.h"
#include "adapters/stm32/config/default/dma_config.h"
#include "adapters/stm32/config/default/gpio_config.h"
#include "adapters/stm32/config/default/nvic_config.h"
#include "adapters/stm32/config/default/rcc_config.h"
#include "adapters/stm32/config/default/serial_config.h"
#include "adapters/stm32/config/default/timer_config.h"

/** @} */

#endif //INJECTOR_DEFAULT_H