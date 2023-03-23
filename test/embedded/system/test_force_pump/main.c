/**
  ******************************************************************************
  * @file   main.c
  * @author Jonathan Taylor
  * @date   21 Mar 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "force_pump.h"
#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g031xx.h"

static Device self;

static Peripherals hal;

int main()
{
    hal = bootstrap(stm32_dependency_injection, 0);
    self = force_pump_create(hal, USART1, TIM2);
    force_pump_run(self);
}
