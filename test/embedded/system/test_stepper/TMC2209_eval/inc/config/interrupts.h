/**
  ******************************************************************************
  * @file   interrupts.h
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

#ifndef INJECTOR_INTERRUPTS_H
#define INJECTOR_INTERRUPTS_H

/** @brief Enable USART1 interrupt handler */
#define STM32_ENABLE_USART1_IRQn                        1
/** @brief USART1 interrupt priority */
#define STM32_USART1_IRQn_PRIORITY                      0

/** @brief Enable USART2 interrupt handler */
#define STM32_ENABLE_USART2_IRQn                        0
/** @brief USART2 interrupt priority */
#define STM32_USART2_IRQn_PRIORITY                      0

/** @brief Enable LPUART1 interrupt handler */
#define STM32_ENABLE_LPUART1_IRQn                       0
/** @brief LPUART1 interrupt priority */
#define STM32_LPUART1_IRQn_PRIORITY                     0

/** @} */
#endif //INJECTOR_INTERRUPTS_H
