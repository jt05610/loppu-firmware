/**
  ******************************************************************************
  * @file   main.c
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  ADC embedded system test runner.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "stm32g0xx_interface.h"

static Peripherals hal;

int main()
{
    hal = bootstrap(stm32_dependency_injection, 0);
    adc_start(hal->analog, 0);
    while (1) {

    }
}