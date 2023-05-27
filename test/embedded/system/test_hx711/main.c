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
    device       = hx711_create(hal, SPI1);
    uint32_t sum;
    uint8_t n = 0;
    while (true) {

        hx711_poll(device);
        n++;
        if (n > 10) {
            sum          = hx711_read(device);
            char out[10] = {0};
            if (sum > 0) {
                itoa(sum, out, 10);
                out[strlen(out)] = '\n';
                serial_write(hal->serial, USART1, (uint8_t *) out, strlen(out));
            }
            n = 0;
        }
    }
}

int
main()
{
    hal = bootstrap(stm32_dependency_injection, 0);
    serial_open(hal->serial, USART1);
    UNITY_BEGIN();
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
