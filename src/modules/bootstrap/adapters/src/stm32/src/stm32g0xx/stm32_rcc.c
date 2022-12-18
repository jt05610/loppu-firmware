/**
  ******************************************************************************
  * @file   stm32_rcc.c
  * @author Jonathan Taylor
  * @date   7/1/22
  * @brief Source for initializing stm32 hardware clock.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_utils.h"

#include "stm32_rcc.h"
#include "default.h"

static inline void sys_clock_init();

static inline void gpio_clock_init();

static inline void dma_clock_init();

static inline void serial_clock_init();

static inline void timer_clock_init();

static inline void adc_clock_init();


void
stm32_rcc_config()
{
    sys_clock_init();

#if STM32_ENABLE_GPIO
    gpio_clock_init();
#endif

#if STM32_ENABLE_DMA
    dma_clock_init();
#endif

#if STM32_ENABLE_ADC
    adc_clock_init();
#endif

#if STM32_ENABLE_TIMER
    timer_clock_init();
#endif

#if STM32_ENABLE_SERIAL
    serial_clock_init();
#endif
}

static inline void
sys_clock_init()
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    NVIC_SetPriority(SysTick_IRQn, 3);

    LL_RCC_HSI_Enable();
#ifndef SIMULATED
    while (LL_RCC_HSI_IsReady() != 1);
#endif
    LL_RCC_SetAHBPrescaler(STM32_AHB_PRESCALER);
    LL_RCC_SetSysClkSource(STM32_SYS_CLK_SOURCE);

#ifndef SIMULATED
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI);
#endif

    LL_RCC_SetAPB1Prescaler(STM32_APB1_PRESCALER);

    LL_Init1msTick(STM32_SYS_TICK);

    LL_SetSystemCoreClock(STM32_SYS_TICK);
}

static inline void
gpio_clock_init()
{
#if STM32_ENABLE_GPIOA
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
#endif

#if STM32_ENABLE_GPIOB
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
#endif

#if STM32_ENABLE_GPIOC
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
#endif

#if STM32_ENABLE_GPIOD
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);
#endif

#if STM32_ENABLE_GPIOF
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);
#endif
}

static inline void
dma_clock_init()
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
}

static inline void
serial_clock_init()
{
#if STM32_ENABLE_USART1
    LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
#endif

#if STM32_ENABLE_USART2
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
#endif
}

static inline void
timer_clock_init()
{
#if STM32_ENABLE_LPTIM1
    LL_RCC_SetLPTIMClockSource(STM32_LPTIM1_CLOCK_SOURCE);

#endif // STM32_ENABLE_LPTIM1

#if STM32_ENABLE_LPTIM2
    LL_RCC_SetLPTIMClockSource(STM32_LPTIM2_CLOCK_SOURCE);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM2);
#endif // STM32_ENABLE_LPTIM2

#if STM32_ENABLE_RTC
    if (LL_RCC_GetRTCClockSource() != STM32_RTC_CLOCK_SOURCE) {
        LL_RCC_ForceBackupDomainReset();
        LL_RCC_ReleaseBackupDomainReset();
        LL_RCC_SetRTCClockSource(STM32_RTC_CLOCK_SOURCE);
    }
    LL_RCC_EnableRTC();
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_RTC);
#endif // STM32_ENABLE_RTC

#if STM32_ENABLE_TIM1
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
#endif // STM32_ENABLE_TIM1

#if STM32_ENABLE_TIM2
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
#endif // STM32_ENABLE_TIM2

#if STM32_ENABLE_TIM3
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
#endif // STM32_ENABLE_TIM3

#if STM32_ENABLE_TIM14
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM14);
#endif // STM32_ENABLE_TIM14

#if STM32_ENABLE_TIM16
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);
#endif // STM32_ENABLE_TIM16

#if STM32_ENABLE_TIM17
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17);
#endif // STM32_ENABLE_TIM17
}

static inline void
adc_clock_init()
{
    LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_SYSCLK);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC);
}
