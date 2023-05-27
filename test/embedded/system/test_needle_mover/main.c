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

#include "needle_mover.h"
#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g031xx.h"
#include "ic/tmc2209_stepper.h"
#include "stm32g0xx_ll_gpio.h"

static Device self;

static Peripherals hal;
static Stepper     stepper;
static StepDir     stepdir;
static Axis        axis;

int main()
{
    hal = bootstrap(stm32_dependency_injection, 0);

    tmc2209_init_t p = {
            .hal=hal,
            .tim_inst=TIM2,
            .uart_inst=USART2,
            .gpio_inst=GPIOA,
            .en_pin=LL_GPIO_PIN_1,
            .step_pin=LL_GPIO_PIN_4,
            .dir_pin=LL_GPIO_PIN_5,
            .inverse_dir=false,
            .limit_pin=LL_GPIO_PIN_0
    };
    stepper = tmc2209_stepper_create(&p);

    stepdir = stepdir_create(stepper, STEPDIR_FREQ, STEPDIR_FREQ);
    axis    = axis_create(stepdir);
    self    = needle_mover_create(hal, USART1, TIM2,  axis);
    //timer_start(hal->timer, TIM2, STEPDIR_FREQ);
    needle_mover_run(self);
}
