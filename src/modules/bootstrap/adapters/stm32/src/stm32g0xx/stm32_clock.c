/**
  ******************************************************************************
  * @file   stm32_clock.c
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
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_interface.h"

#include "stm32_clock.h"

void
stm32_clock_config()
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    NVIC_SetPriority(SysTick_IRQn, 3);

    LL_RCC_HSI_Enable();
#ifndef SIMULATED
    while (LL_RCC_HSI_IsReady() != 1);
#endif
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

#ifndef SIMULATED
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI);
#endif

    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

    LL_Init1msTick(STM32_SYS_TICK);
    LL_SetSystemCoreClock(STM32_SYS_TICK);
}
