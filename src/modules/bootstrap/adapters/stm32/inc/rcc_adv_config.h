/**
  ******************************************************************************
  * @file   rcc_adv_config.h
  * @author Jonathan Taylor
  * @date   2/14/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_RCC_ADV_CONFIG_H
#define INJECTOR_RCC_ADV_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup STM32G0xx_RCCAdvConfig RCC advanced config
 * @ingroup STM32G0xx_RCC
 * @ingroup STM32G0xx_AdvConfig
 * @brief RCC advanced configuration
 * @{
 */

/** @brief AHB prescaler */
#define STM32_AHB_PRESCALER             LL_RCC_SYSCLK_DIV_1

/** @brief Sys clock source */
#define STM32_SYS_CLK_SOURCE            LL_RCC_SYS_CLKSOURCE_HSI

/** @brief APB1 prescaler */
#define STM32_APB1_PRESCALER            LL_RCC_APB1_DIV_1

/** @} */

#ifdef __cplusplus
};
#endif

#endif //INJECTOR_RCC_ADV_CONFIG_H
