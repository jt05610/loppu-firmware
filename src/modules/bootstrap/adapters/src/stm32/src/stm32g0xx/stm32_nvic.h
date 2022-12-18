/**
  ******************************************************************************
  * @file   stm32_nvic.h
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_STM32_NVIC_H
#define INJECTOR_STM32_NVIC_H

/**
 * @defgroup STM32G0xx_NVIC Nested vectored interrupt controller (NVIC)
 * @ingroup STM32G0xx
 * @brief Manages interrupts
 * @{
 */

/**
 * @brief initializes NVIC
 * @see nvic_config.h
 */
void stm32_nvic_init();

/** @} */

#endif //INJECTOR_STM32_NVIC_H
