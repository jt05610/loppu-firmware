/**
  ******************************************************************************
  * @file   nvic_config.h
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

#ifndef INJECTOR_NVIC_CONFIG_H
#define INJECTOR_NVIC_CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

/** @brief Enable EXTI Line 0 and 1 interrupt handler */
#define STM32_ENABLE_EXTI0_1_IRQn                       0
/** @brief EXTI Line 0 and 1 interrupt priority */
#define STM32_EXTI0_1_IRQn_PRIORITY                     0

/** @brief Enable EXTI Line 2 and 3 interrupt handler */
#define STM32_ENABLE_EXTI2_3_IRQn                       0
/** @brief EXTI Line 2 and 3 interrupt priority */
#define STM32_EXTI2_3_IRQn_PRIORITY                     0

/** @brief Enable EXTI Line 4 to 15 interrupt handler */
#define STM32_ENABLE_EXTI4_15_IRQn                      1
/** @brief EXTI Line 4 to 15 interrupt priority */
#define STM32_EXTI4_15_IRQn_PRIORITY                    0

/**
 * @ingroup STM32G0xx_DMA
 * @{
 */
/** @brief Enable DMA1 Channel 1 interrupt handler */
#define STM32_ENABLE_DMA1_Channel1_IRQn                 1
/** @brief DMA1 Channel 1 interrupt priority */
#define STM32_DMA1_Channel1_IRQn_PRIORITY               0

/** @brief Enable DMA1 Channel 2 and Channel 3 interrupt handler */
#define STM32_ENABLE_DMA1_Channel2_3_IRQn               0
/** @brief DMA1 Channel 2 and Channel 3 interrupt priority */
#define STM32_DMA1_Channel2_3_PRIORITY                  0

/** @brief Enable DMA1 Channel 4 5, DMAMUX1 overrun interrupt handler */
#define STM32_ENABLE_DMA1_Ch4_5_DMAMUX1_OVR_IRQn        0
/** @brief DMA1 Channel 4 to Channel 5, DMAMUX1 overrun interrupt priority */
#define STM32_Channel4_5_DMAMUx1_OVR_IRQn_PRIORITY      0

/** @} */

/**
 * @ingroup STM32G031xx_ADC
 * @{
 */
/** @brief Enable ADC1 interrupt handler */
#define STM32_ENABLE_ADC1_IRQn                          0
/** @brief ADC1 interrupt priority */
#define STM32_ADC1_IRQn_PRIORITY                        0
/** @} */

/**
 * @ingroup STM32G031xx_Timer
 * @{
 */

/** @brief Enable TIM1 Break, Update, Trigger, and Commutation
 *         interrupt handler */
#define STM32_ENABLE_TIM1_BRK_UP_TRG_COM_IRQn           1
/** @brief TIM1 Break, Update, Trigger and Commutation interrupt priority */
#define STM32_TIM1_BRK_UP_TRG_COM_IRQn_PRIORITY         0

/** @brief Enable TIM1 Capture Compare interrupt handler */
#define STM32_ENABLE_TIM1_CC_IRQn                       0
/** @brief TIM1 Capture Compare interrupt priority */
#define STM32_TIM1_CC_IRQn_PRIORITY                     0

/** @brief Enable TIM2 interrupt handler */
#define STM32_ENABLE_TIM2_IRQn                          1
/** @brief TIM2 interrupt priority */
#define STM32_TIM2_IRQn_PRIORITY                        1

/** @brief Enable TIM3 interrupt handler */
#define STM32_ENABLE_TIM3_IRQn                          1
/** @brief TIM3 interrupt priority */
#define STM32_TIM3_IRQn_PRIORITY                        0

/** @brief Enable LPTIM1 interrupt handler */
#define STM32_ENABLE_LPTIM1_IRQn                        0
/** @brief LPTIM1 interrupt priority */
#define STM32_LPTIM1_IRQn_PRIORITY                      0

/** @brief Enable LPTIM2 interrupt handler */
#define STM32_ENABLE_LPTIM2_IRQn                        0
/** @brief LPTIM2 interrupt priority */
#define STM32_LPTIM2_IRQn_PRIORITY                      0

/** @brief Enable TIM14 interrupt handler */
#define STM32_ENABLE_TIM14_IRQn                         0
/** @brief TIM14 interrupt priority */
#define STM32_TIM14_IRQn_PRIORITY                       0

/** @brief Enable TIM16 interrupt handler */
#define STM32_ENABLE_TIM16_IRQn                         0
/** @brief TIM16 interrupt priority */
#define STM32_TIM16_IRQn_PRIORITY                       0

/** @brief Enable TIM17 interrupt handler */
#define STM32_ENABLE_TIM17_IRQn                         0
/** @brief TIM17 interrupt priority */
#define STM32_TIM17_IRQn_PRIORITY                       1

/** @} */
/**
 * @ingroup STM32G031xx_I2C
 * @{
 */

/** @brief Enable I2C1 interrupt handler */
#define STM32_ENABLE_I2C1_IRQn                          0
/** @brief I2C1 interrupt priority */
#define STM32_I2C1_IRQn_PRIORITY                        0

/** @brief Enable I2C2 interrupt handler */
#define STM32_ENABLE_I2C2_IRQn                          0
/** @brief I2C2 interrupt priority */
#define STM32_I2C2_IRQn_PRIORITY                        0

/** @} */

/**
 * @ingroup STM32G031xx_SPI
 * @{
 */

/** @brief Enable SPI1 interrupt handler */
#define STM32_ENABLE_SPI1_IRQn                          0
/** @brief SPI1 interrupt priority */
#define STM32_SPI1_IRQn_PRIORITY                        0

/** @brief Enable SPI2 interrupt handler */
#define STM32_ENABLE_SPI2_IRQn                          0
/** @brief SPI2 interrupt priority */
#define STM32_SPI2_IRQn_PRIORITY                        0

/** @} */

/**
 * @ingroup STM32G031xx_Serial
 * @{
 */

/** @brief Enable USART1 interrupt handler */
#define STM32_ENABLE_USART1_IRQn                        1
/** @brief USART1 interrupt priority */
#define STM32_USART1_IRQn_PRIORITY                      1

/** @brief Enable USART2 interrupt handler */
#define STM32_ENABLE_USART2_IRQn                        1
/** @brief USART2 interrupt priority */
#define STM32_USART2_IRQn_PRIORITY                      0

/** @brief Enable LPUART1 interrupt handler */
#define STM32_ENABLE_LPUART1_IRQn                       0
/** @brief LPUART1 interrupt priority */
#define STM32_LPUART1_IRQn_PRIORITY                     0

/** @} */

/** @) */

#ifdef __cplusplus
};
#endif

#endif //INJECTOR_NVIC_CONFIG_H
