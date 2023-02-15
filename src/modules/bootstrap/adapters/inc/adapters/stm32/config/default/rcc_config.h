/**
  ******************************************************************************
  * @file   rcc_config.h
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  Default clock configuration header for STM32G0xx.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef STM32_RCC_CONFIG_H
#define STM32_RCC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup STM32G0xx_RCCConfig RCC config
 * @ingroup STM32G0xx_RCC
 * @ingroup STM32G0xx_DefaultConfig
 * @brief RCC configuration
 * @{
 */

#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"

/** @brief STM32G0xx system clock tick. */
#define STM32_SYS_TICK                  16000000

/** @} */

#ifdef __cplusplus
};
#endif

#endif // STM32_RCC_CONFIG_H
