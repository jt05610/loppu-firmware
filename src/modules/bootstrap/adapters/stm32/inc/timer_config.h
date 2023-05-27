/**
  ******************************************************************************
  * @file   timer_config.h
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

#ifndef INJECTOR_TIMER_CONFIG_H
#define INJECTOR_TIMER_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup STM32G0xx_TimerConfig Timer config
 * @ingroup STM32G0xx_Timer
 * @ingroup STM32G0xx_DefaultConfig
 * @brief Default timer configuration for STM32g0xx.
 * @{
 */


#define STM32_ENABLE_TIMER              1
/**
  ******************************************************************************
 * @defgroup STM32G0xx_LPTIM1_Config LPTIM1
 * @brief STM32G0xx LPTIM1 configuration
 * @{
 */

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM1_Config TIM1
 * @brief STM32G0xx TIM1 configuration
 * @{
 */

/** @brief Enable Timer 1 */
#define STM32_ENABLE_TIM1               1

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM2_Config TIM2
 * @brief STM32G0xx TIM2 configuration
 * @{
 */

/** @brief Enable Timer 2 */
#define STM32_ENABLE_TIM2               1

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM3_Config TIM3
 * @brief STM32G0xx TIM3 configuration
 * @{
 */

/** @brief Enable Timer 3 */
#define STM32_ENABLE_TIM3               1

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM14_Config TIM14
 * @brief STM32G0xx TIM14 configuration
 * @{
 */

/** @brief Enable Timer 14 */
#define STM32_ENABLE_TIM14              0

/** @} */

/**
  ******************************************************************************
 * @defgroup STM322G0xx_TIM16_Config TIM16
 * @brief STM322G0xx TIM16 configuration
 * @{
 */

/** @brief Enable Timer 16 */
#define STM32_ENABLE_TIM16              0

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM17_Config TIM17
 * @brief STM32G0xx TIM17 configuration
 * @{
 */

/** @brief Enable Timer 17 */
#define STM32_ENABLE_TIM17              1

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif //INJECTOR_TIMER_CONFIG_H

#pragma clang diagnostic pop