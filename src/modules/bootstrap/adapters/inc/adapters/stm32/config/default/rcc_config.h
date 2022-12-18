/**
  ******************************************************************************
  * @file   clock_config.h
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

#ifndef INJECTOR_RCC_CONFIG_H
#define INJECTOR_RCC_CONFIG_H

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

/** @brief AHB prescaler */
#define STM32_AHB_PRESCALER             LL_RCC_SYSCLK_DIV_1

/** @brief Sys clock source */
#define STM32_SYS_CLK_SOURCE            LL_RCC_SYS_CLKSOURCE_HSI

/** @brief APB1 prescaler */
#define STM32_APB1_PRESCALER            LL_RCC_APB1_DIV_1

/** @} */

#endif //INJECTOR_RCC_CONFIG_H
