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
#include "g031xx_adapter.h"
#include "stm32g031xx.h"
#include "ic/tmc2209_stepper.h"
#include "stm32g0xx_ll_gpio.h"

static Device self;

static Peripherals hal;
static Stepper stepper;
static StepDir stepdir;
static Axis axis;

int main() {

    hal = bootstrap(stm32_dependency_injection, 0);
    tmc2209_init_t p = {
            .hal=hal,
            .tim_inst=TIM2,
            .uart_inst=USART2,
            .gpio_inst=GPIOA,
            .en_pin=LL_GPIO_PIN_8,
            .step_pin=LL_GPIO_PIN_1,
            .dir_pin=LL_GPIO_PIN_0,
            .inverse_dir=false,
            .limit_pin=LL_GPIO_PIN_5
    };

    stepper = tmc2209_stepper_create(&p);
    stepdir = stepdir_create(stepper, STEPDIR_FREQ, STEPDIR_FREQ);
    axis_params_t ap = {
            .steps_per_m=203718,
            .ms=MS_64,
            .step_dir=stepdir,
            .max_pos=65535,
            .max_vel=37500,
            .accel=10000,
    };
    axis = axis_create(&ap);
    valve_2_pos_t params = {
            .hal=hal,
            .axis=axis,
            .uart_inst=USART1,
            .tim_inst=TIM1,
            .hx711_tim_inst=TIM17,
            .spi_inst=SPI1,
    };
    self = valve_2_pos_create(&params);
    while (1) {
        valve_2_pos_run(self);
    }
}
