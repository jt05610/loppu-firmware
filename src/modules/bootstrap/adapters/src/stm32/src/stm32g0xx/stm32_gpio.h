/**
  ******************************************************************************
  * @file   stm32_gpio.h
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_STM32_GPIO_H
#define INJECTOR_STM32_GPIO_H

/**
 * @defgroup STM32G0xx_GPIO GPIO peripheral
 * @brief Interface for STM32G0xx GPIO
 * @ingroup STM32G0xx
 * @{
 */

#include "gpio.h"

/**
 * @brief Initializes STM32G0xx GPIO peripherals with parameters defined in
 *        @ref STM32G0xx_GPIOConfig
 * @return Pointer to initialized @ref gpio_t
 */
GPIO stm32_gpio_create();

/** @} */

#endif //INJECTOR_STM32_GPIO_H
