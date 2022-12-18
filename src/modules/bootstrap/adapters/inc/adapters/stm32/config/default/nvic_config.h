/**
  ******************************************************************************
  * @file   nvic_config.h
  * @author Jonathan Taylor
  * @date   12/17/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_NVIC_CONFIG_H
#define INJECTOR_NVIC_CONFIG_H

/**
 * @defgroup STM32G0xx_NVICConfig NVIC config
 * @ingroup STM32G0xx_DefaultConfig
 * @brief NVIC peripheral configuration
 * @{
 */

/**
 * @brief Enables USART1 interrupt generation
 * @ingroup STM32G0xx_USART1_NVIC_Config
 */
#define STM32_ENABLE_USART1_IRQn       0

/**
 * @brief Enables USART2 interrupt generation
 * @ingroup STM32G0xx_USART2_NVIC_Config
 */
#define STM32_ENABLE_USART2_IRQn       0

#if STM32_ENABLE_USART1_IRQn
/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART1_NVIC_Config USART1 interrupts
 * @ingroup STM32G0xx_USART1Config
 * @brief Interrupt generation configuration for USART1
 * @{
 */
/** @brief USART1 interrupt generation priority */
#define STM32_USART1_IRQn_PRIORITY     0

/** @) */
#endif // STM32_ENABLE_USART1_IRQn


#if STM32_ENABLE_USART2_IRQn
/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART2_NVIC_Config USART2 interrupts
 * @brief Interrupt generation configuration for USART2
 * @ingroup STM32G0xx_USART2Config
 * @{
 */

/** @brief USART2 interrupt generation priority */
#define STM32_USART2_IRQn_PRIORITY      0

/** @) */
#endif // STM32_ENABLE_USART2_IRQn

/** @} */
#endif //INJECTOR_NVIC_CONFIG_H
