/**
  ******************************************************************************
  * @file   gpio_config.h
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

#ifndef INJECTOR_GPIO_CONFIG_H
#define INJECTOR_GPIO_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup STM32G0xx_GPIOConfig GPIO config
 * @ingroup STM32G0xx_GPIO
 * @ingroup STM32G0xx_DefaultConfig
 * @brief default configuration for STM32g031xx peripheral.
 * @{
 */

#include "serial_config.h"

#define STM32_ENABLE_GPIO               1    /**< @brief Enable GPIO */

#define STM32_ENABLE_GPIOA              1    /**< @brief Enable GPIO port A */
#define STM32_ENABLE_GPIOB              1    /**< @brief Enable GPIO port B */
#define STM32_ENABLE_GPIOC              0    /**< @brief Enable GPIO port C */
#define STM32_ENABLE_GPIOD              0    /**< @brief Enable GPIO port D */
#define STM32_ENABLE_GPIOF              0    /**< @brief Enable GPIO port E */

/** @} */

#ifdef __cplusplus
}
#endif
#endif //INJECTOR_GPIO_CONFIG_H
