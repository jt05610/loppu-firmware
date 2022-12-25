/**
  ******************************************************************************
  * @file   timer_config.h
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#ifndef INJECTOR_TIMER_CONFIG_H
#define INJECTOR_TIMER_CONFIG_H

/**
 * @defgroup STM32G0xx_TimerConfig Timer config
 * @ingroup STM32G0xx_Timer
 * @ingroup STM32G0xx_DefaultConfig
 * @brief Default timer configuration for STM32g0xx.
 * @{
 */

#include "stm32g0xx_ll_tim.h"

#define STM32_ENABLE_TIMER              1
/**
  ******************************************************************************
 * @defgroup STM32G0xx_LPTIM1_Config LPTIM1
 * @brief STM32G0xx LPTIM1 configuration
 * @{
 */

/** @brief Enable Low power timer 1 */
#define STM32_ENABLE_LPTIM1             0

#if STM32_ENABLE_LPTIM1

/** @brief LPTIM1 clock source */
#define STM32_LPTIM1_CLOCK_SOURCE LL_RCC_LPTIM1_CLKSOURCE_PCLK1

/** @brief Enable LPTIM1 external trigger */
#define STM32_LPTIM1_ENABLE_EXTERNAL_TRIGGER 1

/** @brief Enable LPTIM1 waveform generation */
#define STM32_LPTIM1_ENABLE_WAVEFORM_GEN     1

#if STM32_LPTIM1_ENABLE_WAVEFORM_GEN
#define STM32_LPTIM1_OUTPUT_POLARITY
#endif

#endif

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_LPTIM2_Config LPTIM2
 * @brief STM32G0xx LPTIM2 configuration
 * @{
 */

/** @brief Enable Low power timer 2 */
#define STM32_ENABLE_LPTIM2 0

#if STM32_ENABLE_LPTIM2

/** @brief LPTIM2 clock source */
#define STM32_LPTIM2_CLOCK_SOURCE LL_RCC_LPTIM2_CLKSOURCE_PCLK1

/** @brief LPTIM2 mode */
#define STM32_LPTIM2_MODE

/** @brief LPTIM2 enable external trigger */
#define STM32_LPTIM2_ENABLE_EXTERNAL_TRIGGER 0

#endif

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_RTC_Config RTC
 * @brief STM32G0xx RTC configuration
 * @{
 */

/** @brief Enable real time clock */
#define STM32_ENABLE_RTC 1


#if STM32_ENABLE_RTC

/** @brief RTC clock source */
#define STM32_RTC_CLOCK_SOURCE      LL_RCC_RTC_CLKSOURCE_LSI
/** @brief RTC hour format */
#define STM32_RTC_HOUR_FORMAT       LL_RTC_HOURFORMAT_24HOUR
/** @brief */
#define STM32_RTC_ASYNC_PREDIVIDER  127
/** @brief */
#define STM32_RTC_SYNC_PREDIVIDER   255
#endif

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM1_Config TIM1
 * @brief STM32G0xx TIM1 configuration
 * @{
 */

/** @brief Enable Timer 1 */
#define STM32_ENABLE_TIM1               1

/**
 * @defgroup STM32G0xx_TIM1_NVIC_Config TIM1 interrupts
 * @brief Interrupt generation configuration for TIM1
 * @addtogroup STM32G0xx_NVIC_Config
 * @{
 */

/** @brief Enable TIM1 break, update, trigger, and commutation interrupts */
#define STM32_ENABLE_TIM1_BUTC_IRQn     0

#if STM32_ENABLE_TIM1_BUTC_IRQn
/** @brief TIM1 break, update, trigger, and commutation interrupts priority */
#define STM32_TIM1_BUTC_IRQn_PRIORITY   0
#endif // STM32_ENABLE_TIM1_BUTC_IRQn

/** @brief Enable TIM1 capture_compare interrupt */
#define STM32_ENABLE_TIM1_CC_IRQn       0

#if STM32_ENABLE_TIM1_CC_IRQn
/** @brief TIM1 capture_compare interrupt priority */
#define STM32_TIM1_CC_IRQn_PRIORITY     0
#endif // STM32_ENABLE_TIM1_CC_IRQn

/** @} */

#if STM32_ENABLE_TIM1

/** @brief TIM1 enable Master/Slave mode */
#define STM32_TIM1_M_S_MODE_ENABLE      0

/** @brief TIM1 prescaler */
#define STM32_TIM1_PRESCALER            0

/** @brief TIM1 counter mode */
#define STM32_TIM1_COUNTER_MODE         LL_TIM_COUNTERMODE_UP

/** @brief TIM1 autoreload */
#define STM32_TIM1_AUTORELOAD           65535

/** @brief TIM1 clock division */
#define STM32_TIM1_CLOCK_DIV            LL_TIM_CLOCKDIVISION_DIV1

/** @brief TIM1 repetition counter */
#define STM32_TIM1_REP_COUNTER          0

/** @brief TIM1 Enables or disables ARR preload */
#define STM32_TIM1_ENABLE_ARR_PRELOAD   0

/** @brief TIM1 clock source */
#define STM32_TIM1_CLOCK_SOURCE         LL_TIM_CLOCKSOURCE_INTERNAL

/** @brief TIM1 enables or disables preload */
#define STM32_TIM1_ENABLE_PRELOAD       1

/** @brief TIM1 enable output compare */
#define STM32_TIM1_ENABLE_OC            1

#if STM32_TIM1_ENABLE_OC
/** @brief Output compare mode */
#define STM32_TIM1_OCMODE               LL_TIM_OCMODE_PWM1

/** @brief Output compare state */
#define STM32_TIM1_OCSTATE              LL_TIM_OCSTATE_DISABLE

/** @brief Complementary output compare state */
#define STM32_TIM1_OCNSTATE             LL_TIM_OCSTATE_DISABLE

/** @brief Compare value to be loaded into capture compare register */
#define STM32_TIM1_COMPAREVALUE         0

/** @brief Output polarity */
#define STM32_TIM1_OCPOLARITY           LL_TIM_OCPOLARITY_HIGH

/** @brief Complementary output polarity */
#define STM32_TIM1_OCNPOLARITY          LL_TIM_OCPOLARITY_HIGH

/** @brief TIM output compare pin state during Idle state */
#define STM32_TIM1_OCIDLESTATE          LL_TIM_OCIDLESTATE_LOW

/** @brief TIM complementary output compare pin during Idle state */
#define STM32_TIM1_OCNIDLESTATE         LL_TIM_OCIDLESTATE_LOW

/** @brief Enable or disable fast mode for output channel */
#define STM32_TIM1_ENABLE_FAST          0

/** @brief Trigger output used for timer synchronization  */
#define STM32_TIM1_TRIGGER_OUT1         LL_TIM_TRGO_RESET

/** @brief Trigger output 2 used for timer synchronization */
#define STM32_TIM1_TRIGGER_OUT2         LL_TIM_TRGO2_RESET

/** @brief Off state selection used in run mode. */
#define STM32_TIM1_OSSRSTATE            LL_TIM_OSSR_DISABLE

/** @brief Off state used in idle state. */
#define STM32_TIM1_OSSISTATE            LL_TIM_OSSI_DISABLE

/**
 * @brief LOCK level parameters
 * @note can only be written once after reset.
 * */
#define STM32_TIM1_LOCKLEVEL            LL_TIM_LOCKLEVEL_OFF

/** @brief Delay time before switching off and on of outputs */
#define STM32_TIM1_DEADTIME             0

/** @brief Enable or disables TIM Break input. */
#define STM32_TIM1_BREAKSTATE           LL_TIM_BREAK_DISABLE

/** @brief Specifies TIM Break input pin polarity */
#define STM32_TIM1_BREAKPOLARITY        LL_TIM_BREAK_POLARITY_HIGH

/** @brief Specifies TIM break filter */
#define STM32_TIM1_BREAKFILTER          LL_TIM_BREAK_FILTER_FDIV1

/** @brief Specifies alternate function mode of TIM break input */
#define STM32_TIM1_BREAKAFMODE          LL_TIM_BREAK_AFMODE_INPUT

/** @brief Enable or disables TIM Break2 input. */
#define STM32_TIM1_BREAK2STATE          LL_TIM_BREAK2_DISABLE

/** @brief Specifies TIM Break2 input pin polarity */
#define STM32_TIM1_BREAK2POLARITY       LL_TIM_BREAK2_POLARITY_HIGH

/** @brief Specifies TIM break filter */
#define STM32_TIM1_BREAK2FILTER         LL_TIM_BREAK2_FILTER_FDIV1

/** @brief Specifies alternate function mode of TIM break input */
#define STM32_TIM1_BREAK2AFMODE         LL_TIM_BREAK2_AFMODE_INPUT

/** @brief Enable or disable automatic output */
#define STM32_TIM1_AUTOMATICOUTPUT      LL_TIM_AUTOMATICOUTPUT_DISABLE

#endif // STM32_TIM1_ENABLE_OC

#endif // STM32_ENABLE_TIM1

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM2_Config TIM2
 * @brief STM32G0xx TIM2 configuration
 * @{
 */

/** @brief Enable Timer 2 */
#define STM32_ENABLE_TIM2               1

/**
 * @defgroup STM32G0xx_TIM2_NVIC_Config TIM2 interrupts
 * @brief Interrupt generation configuration for TIM2
 * @addtogroup STM32G0xx_NVIC_Config
 * @{
 */

/** @brief enable or disable TIM2 global interrupt generation */
#define STM32_ENABLE_TIM2_IRQn          0


/** @brief TIM2 interrupt priority */
#define STM32_TIM2_IRQn_priority        0

/** @} */

/** @brief TIM2 enable Master/Slave mode */
#define STM32_TIM2_M_S_MODE_ENABLE      0

/** @brief TIM2 prescaler */
#define STM32_TIM2_PRESCALER            0

/** @brief TIM2 counter mode */
#define STM32_TIM2_COUNTER_MODE         LL_TIM_COUNTERMODE_UP

/** @brief TIM2 autoreload */
#define STM32_TIM2_AUTORELOAD           65535

/** @brief TIM2 clock division */
#define STM32_TIM2_CLOCK_DIV            LL_TIM_CLOCKDIVISION_DIV1

/** @brief TIM2 repetition counter */
#define STM32_TIM2_REP_COUNTER          0

/** @brief TIM2 Enables or disables ARR preload */
#define STM32_TIM2_ENABLE_ARR_PRELOAD   0

/** @brief TIM2 clock source */
#define STM32_TIM2_CLOCK_SOURCE         LL_TIM_CLOCKSOURCE_INTERNAL

/** @brief TIM2 enable output compare */
#define STM32_TIM2_ENABLE_OC            1

/** @brief TIM2 enables or disables preload */
#define STM32_TIM2_ENABLE_PRELOAD       1

/** @brief Output compare mode */
#define STM32_TIM2_OCMODE               LL_TIM_OCMODE_PWM1

/** @brief Output compare state */
#define STM32_TIM2_OCSTATE              LL_TIM_OCSTATE_DISABLE

/** @brief Complementary output compare state */
#define STM32_TIM2_OCNSTATE             LL_TIM_OCSTATE_DISABLE

/** @brief Compare value to be loaded into capture compare register */
#define STM32_TIM2_COMPAREVALUE         0

/** @brief Output polarity */
#define STM32_TIM2_OCPOLARITY           LL_TIM_OCPOLARITY_HIGH

/** @brief Complementary output polarity */
#define STM32_TIM2_OCNPOLARITY          LL_TIM_OCPOLARITY_HIGH

/** @brief TIM output compare pin state during Idle state */
#define STM32_TIM2_OCIDLESTATE          LL_TIM_OCIDLESTATE_LOW

/** @brief TIM complementary output compare pin during Idle state */
#define STM32_TIM2_OCNIDLESTATE         LL_TIM_OCIDLESTATE_LOW

/** @brief Enable or disable fast mode for output channel */
#define STM32_TIM2_ENABLE_FAST          0

/** @brief Trigger output used for timer synchronization  */
#define STM32_TIM2_TRIGGER_OUT1         LL_TIM_TRGO_RESET

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM3_Config TIM3
 * @brief STM32G0xx TIM3 configuration
 * @{
 */

/** @brief Enable Timer 3 */
#define STM32_ENABLE_TIM3               1

/**
 * @defgroup STM32G0xx_TIM3_NVIC_Config TIM3 interrupts
 * @brief Interrupt generation configuration for TIM3
 * @addtogroup STM32G0xx_NVIC_Config
 * @{
 */

/** @brief enable or disable TIM3 global interrupt generation */
#define STM32_ENABLE_TIM3_IRQn          0

#if STM32_ENABLE_TIM3_IRQn
/** @brief TIM3 interrupt priority */
#define STM32_TIM3_IRQn_priority        0
#endif // STM32_ENABLE_TIM3_IRQn

/** @} */

#if STM32_ENABLE_TIM3
/** @brief TIM3 enable Master/Slave mode */
#define STM32_TIM3_M_S_MODE_ENABLE      0

/** @brief TIM3 prescaler */
#define STM32_TIM3_PRESCALER            0

/** @brief TIM3 counter mode */
#define STM32_TIM3_COUNTER_MODE         LL_TIM_COUNTERMODE_UP

/** @brief TIM3 autoreload */
#define STM32_TIM3_AUTORELOAD           65535

/** @brief TIM3 clock division */
#define STM32_TIM3_CLOCK_DIV            LL_TIM_CLOCKDIVISION_DIV1

/** @brief TIM3 repetition counter */
#define STM32_TIM3_REP_COUNTER          0

/** @brief TIM3 Enables or disables ARR preload */
#define STM32_TIM3_ENABLE_ARR_PRELOAD   0

/** @brief TIM3 clock source */
#define STM32_TIM3_CLOCK_SOURCE         LL_TIM_CLOCKSOURCE_INTERNAL

/** @brief TIM3 enables or disables preload */
#define STM32_TIM3_ENABLE_PRELOAD       1

/** @brief TIM3 enable output compare */
#define STM32_TIM3_ENABLE_OC            1

#if STM32_TIM3_ENABLE_OC
/** @brief Output compare mode */
#define STM32_TIM3_OCMODE               LL_TIM_OCMODE_PWM1

/** @brief Output compare state */
#define STM32_TIM3_OCSTATE              LL_TIM_OCSTATE_DISABLE

/** @brief Complementary output compare state */
#define STM32_TIM3_OCNSTATE             LL_TIM_OCSTATE_DISABLE

/** @brief Compare value to be loaded into capture compare register */
#define STM32_TIM3_COMPAREVALUE         0

/** @brief Output polarity */
#define STM32_TIM3_OCPOLARITY           LL_TIM_OCPOLARITY_HIGH

/** @brief Complementary output polarity */
#define STM32_TIM3_OCNPOLARITY          LL_TIM_OCPOLARITY_HIGH

/** @brief TIM output compare pin state during Idle state */
#define STM32_TIM3_OCIDLESTATE          LL_TIM_OCIDLESTATE_LOW

/** @brief TIM complementary output compare pin during Idle state */
#define STM32_TIM3_OCNIDLESTATE         LL_TIM_OCIDLESTATE_LOW

/** @brief Enable or disable fast mode for output channel */
#define STM32_TIM3_ENABLE_FAST          0

/** @brief Trigger output used for timer synchronization  */
#define STM32_TIM3_TRIGGER_OUT1          LL_TIM_TRGO_RESET

#endif // STM32_TIM3_ENABLE_OC

#endif // STM32_ENABLE_TIM3

/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM14_Config TIM14
 * @brief STM32G0xx TIM14 configuration
 * @{
 */

/** @brief Enable Timer 14 */
#define STM32_ENABLE_TIM14              1

/**
 * @defgroup STM32G0xx_TIM14_NVIC_Config TIM14 interrupts
 * @brief Interrupt generation configuration for TIM14
 * @addtogroup STM32G0xx_NVIC_Config
 * @{
 */

/** @brief enable or disable TIM14 global interrupt generation */
#define STM32_ENABLE_TIM14_IRQn         0

#if STM32_ENABLE_TIM14_IRQn
/** @brief TIM14 interrupt priority */
#define STM32_TIM14_IRQn_priority       0
#endif // STM32_ENABLE_TIM14_IRQn

/** @} */

#if STM32_ENABLE_TIM14

/** @brief TIM14 enable Master/Slave mode */
#define STM32_TIM14_M_S_MODE_ENABLE     0

/** @brief TIM14 prescaler */
#define STM32_TIM14_PRESCALER           0

/** @brief TIM14 counter mode */
#define STM32_TIM14_COUNTER_MODE        LL_TIM_COUNTERMODE_UP

/** @brief TIM14 autoreload */
#define STM32_TIM14_AUTORELOAD          65535

/** @brief TIM14 clock division */
#define STM32_TIM14_CLOCK_DIV           LL_TIM_CLOCKDIVISION_DIV1

/** @brief TIM14 repetition counter */
#define STM32_TIM14_REP_COUNTER         0

/** @brief TIM14 Enables or disables ARR preload */
#define STM32_TIM14_ENABLE_ARR_PRELOAD  0

/** @brief TIM14 clock source */
#define STM32_TIM14_CLOCK_SOURCE        LL_TIM_CLOCKSOURCE_INTERNAL

/** @brief TIM14 enables or disables preload */
#define STM32_TIM14_ENABLE_PRELOAD      1

#endif

/** @} */

/**
  ******************************************************************************
 * @defgroup STM322G0xx_TIM16_Config TIM16
 * @brief STM322G0xx TIM16 configuration
 * @{
 */

/** @brief Enable Timer 16 */
#define STM32_ENABLE_TIM16              1

/**
 * @defgroup STM32G0xx_TIM16_NVIC_Config TIM16 interrupts
 * @brief Interrupt generation configuration for TIM16
 * @addtogroup STM32G0xx_NVIC_Config
 * @{
 */

/** @brief enable or disable TIM16 global interrupt generation */
#define STM32_ENABLE_TIM16_IRQn         0

#if STM32_ENABLE_TIM16_IRQn
/** @brief TIM16 interrupt priority */
#define STM32_TIM16_IRQn_priority       0
#endif // STM32_ENABLE_TIM16_IRQn

/** @} */

#if STM32_ENABLE_TIM16

/** @brief TIM16 enable Master/Slave mode */
#define STM32_TIM16_M_S_MODE_ENABLE     0

/** @brief TIM16 prescaler */
#define STM32_TIM16_PRESCALER           0

/** @brief TIM16 counter mode */
#define STM32_TIM16_COUNTER_MODE        LL_TIM_COUNTERMODE_UP

/** @brief TIM16 autoreload */
#define STM32_TIM16_AUTORELOAD          65535

/** @brief TIM16 clock division */
#define STM32_TIM16_CLOCK_DIV           LL_TIM_CLOCKDIVISION_DIV1

/** @brief TIM16 repetition counter */
#define STM32_TIM16_REP_COUNTER         0

/** @brief TIM16 Enables or disables ARR preload */
#define STM32_TIM16_ENABLE_ARR_PRELOAD  0

/** @brief TIM16 clock source */
#define STM32_TIM16_CLOCK_SOURCE        LL_TIM_CLOCKSOURCE_INTERNAL

/** @brief TIM16 enables or disables preload */
#define STM32_TIM16_ENABLE_PRELOAD      1

#endif


/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_TIM17_Config TIM17
 * @brief STM32G0xx TIM17 configuration
 * @{
 */

/** @brief Enable Timer 17 */
#define STM32_ENABLE_TIM17              1

/**
 * @defgroup STM32G0xx_TIM17_NVIC_Config TIM17 interrupts
 * @brief Interrupt generation configuration for TIM17
 * @addtogroup STM32G0xx_NVIC_Config
 * @{
 */

/** @brief enable or disable TIM17 global interrupt generation */
#define STM32_ENABLE_TIM17_IRQn         0

#if STM32_ENABLE_TIM17_IRQn
/** @brief TIM17 interrupt priority */
#define STM32_TIM17_IRQn_priority       0
#endif // STM32_ENABLE_TIM17_IRQn

/** @} */

#if STM32_ENABLE_TIM17

/** @brief TIM17 enable Master/Slave mode */
#define STM32_TIM17_M_S_MODE_ENABLE     0

/** @brief TIM17 prescaler */
#define STM32_TIM17_PRESCALER           0

/** @brief TIM17 counter mode */
#define STM32_TIM17_COUNTER_MODE        LL_TIM_COUNTERMODE_UP

/** @brief TIM17 autoreload */
#define STM32_TIM17_AUTORELOAD          65535

/** @brief TIM17 clock division */
#define STM32_TIM17_CLOCK_DIV           LL_TIM_CLOCKDIVISION_DIV1

/** @brief TIM17 repetition counter */
#define STM32_TIM17_REP_COUNTER         0

/** @brief TIM17 Enables or disables ARR preload */
#define STM32_TIM17_ENABLE_ARR_PRELOAD  0

/** @brief TIM17 clock source */
#define STM32_TIM17_CLOCK_SOURCE        LL_TIM_CLOCKSOURCE_INTERNAL

/** @brief TIM17 enables or disables preload */
#define STM32_TIM17_ENABLE_PRELOAD      1

#endif

/** @} */

/** @} */

#endif //INJECTOR_TIMER_CONFIG_H

#pragma clang diagnostic pop