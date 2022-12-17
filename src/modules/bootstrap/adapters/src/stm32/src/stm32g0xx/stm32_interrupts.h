/**
  ******************************************************************************
  * @file   stm32_interrupts.h
  * @author Jonathan Taylor
  * @date   12/17/22
  * @brief  Function prototypes for STM32G0xx interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_STM32_INTERRUPTS_H
#define INJECTOR_STM32_INTERRUPTS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup STM32G0xx_Interrupts Interrupt handlers
 * @brief Interrupt handlers for STM32G0xx
 * @ingroup STM32G0xx_NVIC
 * @{
 */

/** @brief Return type for interrupt functions to avoid compiler warnings. */
#define __INTERRUPT                     __attribute__((unused)) void

/** @brief Window WatchDog              */
__INTERRUPT WWDG_IRQHandler();

/** @brief PVD through EXTI Line detect */
__INTERRUPT PVD_IRQHandler();

/** @brief RTC through the EXTI line    */
__INTERRUPT RTC_TAMP_IRQHandler();

/** @brief FLASH                        */
__INTERRUPT FLASH_IRQHandler();

/** @brief RCC                          */
__INTERRUPT RCC_IRQHandler();

/** @brief EXTI Line 0 and 1            */
__INTERRUPT EXTI0_1_IRQHandler();

/** @brief EXTI Line 2 and 3            */
__INTERRUPT EXTI2_3_IRQHandler();

/** @brief EXTI Line 4 to 15            */
__INTERRUPT EXTI4_15_IRQHandler();

/** @brief DMA1 Channel 1               */
__INTERRUPT DMA1_Channel1_IRQHandler();

/** @brief DMA1 Channel 2 and Channel 3 */
__INTERRUPT DMA1_Channel2_3_IRQHandler();

/** @brief DMA1 Channel 4 to Channel 5, DMAMUX1 overrun */
__INTERRUPT DMA1_Ch4_5_DMAMUX1_OVR_IRQHandler();

/** @brief ADC1                        */
__INTERRUPT ADC1_IRQHandler();

/** @brief TIM1 Break, Update, Trigger and Commutation */
__INTERRUPT TIM1_BRK_UP_TRG_COM_IRQHandler();

/** @brief TIM1 Capture Compare         */
__INTERRUPT TIM1_CC_IRQHandler();

/** @brief TIM2                         */
__INTERRUPT TIM2_IRQHandler();

/** @brief TIM3                         */
__INTERRUPT TIM3_IRQHandler();

/** @brief LPTIM1                       */
__INTERRUPT LPTIM1_IRQHandler();

/** @brief LPTIM2                       */
__INTERRUPT LPTIM2_IRQHandler();

/** @brief TIM14                        */
__INTERRUPT TIM14_IRQHandler();

/** @brief TIM16                        */
__INTERRUPT TIM16_IRQHandler();

/** @brief TIM17                        */
__INTERRUPT TIM17_IRQHandler();

/** @brief I2C1                         */
__INTERRUPT I2C1_IRQHandler();

/** @brief I2C2                         */
__INTERRUPT I2C2_IRQHandler();

/** @brief SPI1                         */
__INTERRUPT SPI1_IRQHandler();

/** @brief SPI2                         */
__INTERRUPT SPI2_IRQHandler();

/** @brief USART1                       */
__INTERRUPT USART1_IRQHandler();

/** @brief USART2                       */
__INTERRUPT USART2_IRQHandler();

/** @brief LPUART1                      */
__INTERRUPT LPUART1_IRQHandler();

/** @} */

#ifdef __cplusplus
}
#endif

#endif //INJECTOR_STM32_INTERRUPTS_H
