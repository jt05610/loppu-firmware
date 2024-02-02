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

#include "valve_2_pos.h"
#include "g031xx_adapter.h"
#include "stm32g031xx.h"
#include "stm32g0xx_ll_gpio.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
static Device self;

static Peripherals hal;

int main() {

    hal = bootstrap(stm32_dependency_injection, 0);
    valve_2_pos_t p = {
            .hal=hal,
            .tim_inst=TIM2,
            .uart_inst=USART2,
            .gpio_inst=GPIOA,
            .pin=LL_GPIO_PIN_1,
    };

    self = valve_2_pos_create(&p);
    while (1) {
        valve_2_pos_run(self);
    }
}

#pragma clang diagnostic pop