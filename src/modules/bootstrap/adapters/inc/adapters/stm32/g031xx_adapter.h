/**
  ******************************************************************************
  * @file   g0xx_adapter.h
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  STM32G0xx interface header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_G031XX_ADAPTER_H
#define INJECTOR_G031XX_ADAPTER_H

#include "bootstrap.h"

/**@addtogroup Bootstrap
 * @{
 */

/** @addtogroup Adapters
 * @{
 */

/**
 * @defgroup STM32G0xx
 * @brief STM32G0xx HAL implementation.
 * @{
 */

/**
 * @brief  Creates peripheral implementation for stm32g0xx.
 * @param params pointer to @ref stm32init_t.
 * @return STM32G0xx implemented @ref Peripherals.
 */
Peripherals stm32_dependency_injection(void * params);

/** @} */

/** @} */

/** @} */

#endif //INJECTOR_G031XX_ADAPTER_H
