/**
  ******************************************************************************
  * @file   helper_macros.h
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

#ifndef INJECTOR_HELPER_MACROS_H
#define INJECTOR_HELPER_MACROS_H

/**
 * @defgroup STM32G0xx_InterruptHelperMacros
 * @brief Macros to reduce code in interrupt initialization
 * @ingroup STM32G0xx_NVIC
 * @{
 */
/**
 * @brief Executes STM32 low level abstraction function
 * @param periph peripheral
 * @param inst instance
 * @param func function
 * @param flag Which interrupt flag
 */
#define __DO(periph, inst, func, flag) \
LL##periph##_##func##_##flag(inst)

/**
 * @brief Checks if interrupt is enabled
 * @param _periph Peripheral
 * @param _flag Flag to check
 */
#define __IT_IS_ENABLED(periph, flag) STM32##periph##_ENABLE_IT_##flag

/**
 * @brief Enables or disables peripheral based on configuration
 * @param _periph Peripheral
 * @param _inst Peripheral instance
 * @param _flag Flag to check
 */
#define __ENABLE_IT(_periph, _inst, _flag) __IT_IS_ENABLED(_periph, _flag)     \
                          ? __DO(_periph, _inst, EnableIT, _flag)                        \
                          : __DO(_periph, _inst, DisableIT, _flag)

#define __CLEAR_FLAG(_periph, _inst, _flag) \
__DO(_periph, _inst, ClearFlag, _flag)

#define ISR_INIT(_periph, _inst, _flag) __CLEAR_FLAG(_periph, _inst, _flag); __ENABLE_IT(_periph, _inst, _flag)

#define ADC1_ISR_INIT(_flag) ISR_INIT(_ADC, ADC1, _flag)

/** @} */

#endif //INJECTOR_HELPER_MACROS_H
