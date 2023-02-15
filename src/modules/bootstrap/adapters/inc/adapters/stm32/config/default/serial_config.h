/**
  ******************************************************************************
  * @file   serial_config.h
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  Default stm32g0xx serial configuration header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_SERIAL_CONFIG_H
#define INJECTOR_SERIAL_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup STM32G0xx_SerialConfig Serial config
 * @ingroup STM32G0xx_Serial
 * @ingroup STM32G0xx_DefaultConfig
 * @brief Macros to implement stm32g031xx serial peripheral.
 * @{
 */

#define STM32_ENABLE_SERIAL             1 /**< @brief Enable USART peripheral */

/**
 * @brief whether to configure and enable USART1 instance
 * @ingroup STM32G0xx_USART1Config
 * */
#define STM32_ENABLE_USART1             1

/**
 * @brief whether to configure and enable USART2 instance
 * @ingroup STM32G0xx_USART2Config
 * */
#define STM32_ENABLE_USART2             1

#define STM32_ENABLE_USART2_ONEWIRE     0

/** @) */


#ifdef __cplusplus
}
#endif

#endif //INJECTOR_SERIAL_CONFIG_H
