/**
  ******************************************************************************
  * @file   test_linear_axis.c
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

#include "test_linear_axis.h"
#include "ic/tmc2209_stepper.h"
#include "linear_axis.h"
#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_usart.h"
#include "bootstrap.h"
#include "unity.h"

static Peripherals hal;
static Stepper     stepper;
static StepDir     stepdir;
static Axis        axis;

void setUp()
{

}

void tearDown()
{

}

void
test_home()
{
    axis_home(axis);
    while(!axis_homed(axis));
}

int
main()
{
    hal = bootstrap(stm32_dependency_injection, 0);
    tmc2209_init_t p = {
            .hal=hal,
            .tim_inst=TIM2,
            .uart_inst=USART2,
            .gpio_inst=GPIOA,
            .en_pin=1,
            .step_pin=4,
            .dir_pin=5,
            .inverse_dir=false,
            .limit_pin=0
    };
    stepper = tmc2209_stepper_create(&p);
    stepdir = stepdir_create(
            hal, stepper, TIM2, STEPDIR_FREQ, STEPDIR_FREQ, axis_stall_handler);
    axis    = axis_create(stepdir);
    serial_open(hal->serial, USART1);
    serial_open(hal->serial, USART2);
    UNITY_BEGIN();
    RUN_TEST(test_home);
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