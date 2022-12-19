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
#include "adapters/stm32/g031xx_adapter.h"
#include "serial.h"
#include "stm32g0xx_ll_dma.h"

static Peripherals hal;

int main()
{
    uint16_t reading;
    uint32_t cnt = 0;
    hal = bootstrap(stm32_dependency_injection, 0);
    serial_open(hal->serial, USART1);
    while (1) {

    }

}