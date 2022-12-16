/**
  ******************************************************************************
  * @file   stm32_timer.h
  * @author Jonathan Taylor
  * @date   12/13/22
  * @brief  STM32 Timer HAL header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_STM32_TIMER_H
#define INJECTOR_STM32_TIMER_H

#include "timer.h"

/**
 * @addtogroup STM32G0xx
 * @{
 */

/**
 * @defgroup STM32G0xx_Timer
 * @brief STM32G0xx timer implementation.
 * @{
 */

/**
 * @brief Creates STM32G0xx Timer interface.
 * @param params Initialization parameters.
 * @return @ref Timer initialized to interact with STM32G0xx.
 */
Timer stm32_timer_create();

/** @} */

/** @} */

#endif //INJECTOR_STM32_TIMER_H
