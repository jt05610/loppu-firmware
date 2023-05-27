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


#include "adc_adv_config.h"
#include "dma_adv_config.h"
#include "gpio_adv_config.h"
#include "nvic_adv_config.h"
#include "rcc_adv_config.h"
#include "serial_adv_config.h"
#include "timer_adv_config.h"

#ifndef USERCONFIG
#endif

#include "adc_config.h"
#include "dma_config.h"
#include "gpio_config.h"
#include "nvic_config.h"
#include "rcc_config.h"
#include "timer_config.h"
#include "serial_config.h"
#include "spi_config.h"

/** @} */

#endif //INJECTOR_DEFAULT_H
