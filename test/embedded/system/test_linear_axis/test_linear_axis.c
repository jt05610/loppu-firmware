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

#include "ic/tmc2209_stepper.h"
#include "linear_axis.h"
#include "stm32/g031xx_adapter.h"
#include "stm32g0xx_ll_tim.h"
#include "bootstrap.h"
#include "unity.h"
#include "stm32g0xx_ll_gpio.h"

static Peripherals hal;
static Stepper     stepper;
static StepDir     stepdir;
static Axis        axis;

int16_t pos;
char    buff[20];

void setUp()
{
    stepper_set_enabled(stepper, true);
}

void tearDown()
{
    stepper_set_enabled(stepper, false);
}


void
test_home()
{
    axis_home(axis);
    while (!axis_homed(axis)) {
        axis_update(axis);
    }
    TEST_PASS();
}

void
test_goto()
{
#define TARGET 1000

    int32_t actual;
    int32_t start_pos;
    start_pos = stepdir_get_pos(stepdir);
    actual    = start_pos;
    pos       = stepdir_get_pos(stepdir);
    axis_goto(axis, TARGET);
    while ((STEPS_PER_MM * 16) > pos) {}

}

void
test_nudge()
{
    int32_t start_pos;
    pos = stepdir_get_pos(stepdir);
    for (uint8_t i = 0; i < 3; i++) {
        start_pos = pos;
        axis_nudge(axis, 1000);
        while ((STEPS_PER_MM * 16) + start_pos > (pos + 2)) {
        }
    }

}

void
test_stops_at_max()
{
    axis_forward_stall(axis);
    while (axis_state(axis) == AXIS_FORWARD_STALL) {
        axis_update(axis);
    }
    TEST_PASS();
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
            .en_pin=LL_GPIO_PIN_8,
            .step_pin=LL_GPIO_PIN_1,
            .dir_pin=LL_GPIO_PIN_0,
            .inverse_dir=false,
            .limit_pin=LL_GPIO_PIN_5
    };
    stepper = tmc2209_stepper_create(&p);

    stepdir = stepdir_create(stepper, STEPDIR_FREQ, STEPDIR_FREQ);
    axis    = axis_create(stepdir);
    serial_open(hal->serial, USART1);
    uint8_t loops = 1;
    UNITY_BEGIN();
    while (loops--){
        RUN_TEST(test_home);
        RUN_TEST(test_stops_at_max);
    }
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