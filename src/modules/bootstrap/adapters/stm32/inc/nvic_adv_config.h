/**
  ******************************************************************************
  * @file   nvic_adv_config.h
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

#ifndef INJECTOR_NVIC_ADV_CONFIG_H
#define INJECTOR_NVIC_ADV_CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup STM32G0xx_NVICConfig NVIC config
 * @ingroup STM32G0xx_DefaultConfig
 * @brief NVIC peripheral configuration
 * @{
 */

/**
 * @defgroup STM32G0xx_NVICAdvConfig NVIC advanced config
 * @ingroup STM32G0xx_AdvConfig
 * @brief NVIC peripheral advanced configuration
 * @{
 */
/** @brief Enable Window Watchdog interrupt handler */
#define STM32_ENABLE_WWDG_IRQn                          0
/** @brief Window Watchdog interrupt priority */
#define STM32_WWDG_IRQn_PRIORITY                        0

/** @brief Enable PVD through EXTI Line detect */
#define STM32_ENABLE_PVD_IRQn                           0
/** @brief PVD through EXTI Line detect */
#define STM32_PVD_IRQn_PRIORITY                         0

/** @brief Enable RTC through the EXTI line interrupt handler */
#define STM32_ENABLE_RTC_TAMP_IRQn                      0
/** @brief RTC through the EXTI line interrupt priority */
#define STM32_RTC_TAMP_IRQn_PRIORITY                    0

/** @brief Enable FLASH interrupt handler */
#define STM32_ENABLE_FLASH_IRQn                         0
/** @brief FLASH interrupt priority */
#define STM32_FLASH_IRQn_PRIORITY                       0


/** @) */

#ifdef __cplusplus
};
#endif

#endif //INJECTOR_NVIC_ADV_CONFIG_H
