/**
  ******************************************************************************
  * @file   stm32_rcc.h
  * @author Jonathan Taylor
  * @date   7/1/22
  * @brief  STM32 RCC header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef STM32_IMPL_STM32_CLOCK_H
#define STM32_IMPL_STM32_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup STM32G0xx_RCC Reset and clock control (RCC)
 * @ingroup STM32G0xx
 * @brief Handles reset and clock configuration
 * @{
 */

/**
 * @brief Configures rcc
 * @see rcc_config.h
 */
void stm32_rcc_config();

/** @) */

#ifdef __cplusplus
};
#endif

#endif //STM32_IMPL_STM32_CLOCK_H
