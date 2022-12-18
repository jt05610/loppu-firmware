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


#if STM32_ENABLE_GPIOA
/**
  ******************************************************************************
 * @defgroup STM32G0xx_GPIOAConfig GPIOA
 * @brief GPIOA config
 * @{
 */

/** @} */
#endif //STM32_ENABLE_GPIOA

#if STM32_ENABLE_GPIOB
/**
  ******************************************************************************
 * @defgroup STM32G0xx_GPIOBConfig GPIOB
 * @{
 * @brief GPIOB config
 */

/** @} */
#endif //STM32_ENABLE_GPIOB

#if STM32_ENABLE_GPIOC
/**
  ******************************************************************************
 * @defgroup STM32G0xx_GPIOCConfig GPIOC
 * @brief GPIOC config
 * @{
 */

/** @} */
#endif //STM32_ENABLE_GPIOC

#if STM32_ENABLE_GPIOD
/**
  ******************************************************************************
 * @defgroup STM32G0xx_GPIODConfig GPIOD
 * @brief GPIOD config
 * @{
 */

/** @} */
#endif //STM32_ENABLE_GPIOD

#if STM32_ENABLE_GPIOF
/**
  ******************************************************************************
 * @defgroup STM32G0xx_GPIOFConfig GPIOF
 * @brief GPIOF config
 * @{
 */

/** @} */
#endif //STM32_ENABLE_GPIOF

#if STM32_ENABLE_GPIOA
/**
  ******************************************************************************
 * @defgroup STM32G0xx_GPIOAConfig GPIOA
 * @{
 */

/** @} */
#endif //STM32_ENABLE_GPIOA

#if STM32_ENABLE_USART1
/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART1_GPIOConfig USART1 GPIO
 * @brief GPIO config for USART1 peripheral
 * @ingroup STM32G0xx_USART1Config
 * @{
 */

/** @brief GPIO pin to use for RX */
#define STM32_USART1_RX_PIN             LL_GPIO_PIN_7
/** @brief GPIO port to use for RX */
#define STM32_USART1_RX_PORT            GPIOB

/** @brief GPIO pin to use for TX */
#define STM32_USART1_TX_PIN             LL_GPIO_PIN_6
/** @brief GPIO port to use for TX */
#define STM32_USART1_TX_PORT            GPIOB

/** @brief GPIO pin for RE */
#define STM32_USART1_RE_PIN             LL_GPIO_PIN_11
/** @brief GPIO port for RE */
#define STM32_USART1_RE_PORT            GPIOA

/** @brief GPIO pin for DE */
#define STM32_USART1_DE_PIN             LL_GPIO_PIN_12
/** @brief GPIO port for DE */
#define STM32_USART1_DE_PORT            GPIOA


/** @} */
#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART2_GPIOConfig USART2 GPIO
 * @brief GPIO config for USART2 peripheral
 * @ingroup STM32G0xx_USART2Config
 * @{
 */

/** @brief GPIO pin to use for RX */
#define STM32_USART2_RX_PIN             LL_GPIO_PIN_3
/** @brief GPIO port to use for RX */
#define STM32_USART2_RX_PORT            GPIOA

/** @brief GPIO pin to use for TX */
#define STM32_USART2_TX_PIN             LL_GPIO_PIN_2
/** @brief GPIO port to use for TX */
#define STM32_USART2_TX_PORT            GPIOA

/** @brief GPIO pin for RE */
#define STM32_USART2_RE_PIN             LL_GPIO_PIN_1
/** @brief GPIO port for RE */
#define STM32_USART2_RE_PORT            GPIOA

/** @brief GPIO pin for DE */
#define STM32_USART2_DE_PIN             LL_GPIO_PIN_4
/** @brief GPIO port for DE */
#define STM32_USART2_DE_PORT            GPIOA

/** @} */
#endif // STM32_ENABLE_USART2

/** @} */

#endif //INJECTOR_GPIO_CONFIG_H
