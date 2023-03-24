/**
  ******************************************************************************
  * @file   main.c
  * @author Jonathan Taylor
  * @date   2/18/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <string.h>
#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_gpio.h"
#include "bootstrap.h"
#include "unity.h"
#include "hx711.h"
#include "stdlib.h"

static volatile Peripherals hal;

static HX711 device;

void
setUp()
{
}

void
tearDown()
{
}

void
testClockPulses()
{
    char     out[10] = {0, 0, 0, 0, 0, 0};
    uint16_t t;
    uint16_t go_to;
    while (true) {
        t          = timer_get_tick(hal->timer, TIM17);
        go_to      = t + 250;
        while (t < go_to) {
            t = timer_get_tick(hal->timer, TIM17);
        uint16_t}
        uint16_t v = adc_average(hal->analog);
        itoa(v, out, 10);
        out[strlen(out)] = '\n';
        serial_write(hal->serial, USART1, (uint8_t *) out, strlen(out));
        for (uint8_t i = 0; i < 10; i++) {
            out[i] = 0;
        }
    }
}

int
main()
{
    hal = bootstrap(stm32_dependency_injection, 0);
    adc_start(hal->analog);
    serial_open(hal->serial, USART1);
    timer_start(hal->timer, TIM17, 100000);
    RUN_TEST(testClockPulses);
    UNITY_END();
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
    while (1);
}
