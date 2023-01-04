/**
  ******************************************************************************
  * @file   main.c
  * @author Jonathan Taylor
  * @date   1/4/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g031xx.h"

#include "pressure_sensor.h"

static Device self;
int main() {
    self = pressure_sensor_create(bootstrap(stm32_dependency_injection, 0), USART1, TIM1);
    pressure_sensor_run(self);
}
