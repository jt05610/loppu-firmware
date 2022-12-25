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
#include "test_timer.h"
#include "stm32g031xx.h"
#include "unity_config.h"


static Peripherals hal;

static uint8_t result[10];

int main()
{
    hal = bootstrap(stm32_dependency_injection, 0);
    setup_timer(hal->timer, TIM2);
    run_all_tests();
    while (1) {}
}

uint8_t
unity_output_char(char a)
{
    return serial_putchar(hal->serial, USART1, a);
}

void
unity_output_start()
{

}

void
unity_output_flush()
{

}

void
unity_output_complete()
{

}
