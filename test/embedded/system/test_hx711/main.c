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
#include "stm32/g031xx_adapter.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_gpio.h"
#include "bootstrap.h"
#include "unity.h"
#include "hx711.h"
#include "stdlib.h"

static volatile Peripherals hal;

static HX711 device;

void
setUp() {
}

void
tearDown() {
}

void
testClockPulses() {
    device = hx711_create(hal, SPI1, TIM17, 75);
    hx711_start(device);
    uint32_t sum;
    uint32_t n_updates = 10000;
    while (n_updates) {
        if (hx711_poll(device)) {
            char out[10] = {0};
            sum = hx711_read(device);
            if (sum > 10000 && sum != 3408127) {
                n_updates--;
                itoa(sum, out, 10);
                out[strlen(out)] = '\n';
                serial_write(hal->serial, USART1, (uint8_t *) out, strlen(out));
            }
        }
    }
    hx711_stop(device);
}

int
main() {
    hal = bootstrap(stm32_dependency_injection, 0);
    serial_open(hal->serial, USART1);
    UNITY_BEGIN();
    RUN_TEST(testClockPulses);
    UNITY_END();
}

uint8_t
unity_output_char(char a) {
    return serial_putchar(hal->serial, USART1, a);
}

void
unity_output_start() {

}

void
unity_output_flush() {

}

void
unity_output_complete() {
    while (1);
}
