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

#include <stdlib.h>
#include <string.h>
#include "test_linear_axis.h"
#include "ic/tmc2209_stepper.h"
#include "linear_axis.h"
#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_usart.h"
#include "bootstrap.h"
#include "unity.h"
#include "stm32g0xx_ll_gpio.h"

static Peripherals hal;
static Stepper     stepper;
static StepDir     stepdir;
static Axis        axis;

char buff[20];

void setUp()
{
    for (uint8_t i = 0; i < 20; i++) {
        buff[i] = 0;
    }
    stepper_set_enabled(stepper, true);
}

void tearDown()
{

    stepper_set_enabled(stepper, false);
}

void
test_home()
{
    int32_t pos;
    axis_home(axis);
    while (!axis_homed(axis)) {
        pos = tmc2209_tstep_result();
        itoa(pos, buff, 10);
        buff[strlen(buff)] = '\n';
        serial_write(hal->serial, USART1, (uint8_t *) buff, strlen(buff));
    }
    TEST_PASS();
}

void
test_stops_at_max()
{
    int32_t pos;
    stepdir_rotate(stepdir, STEPDIR_MAX_VELOCITY);
    while (axis_state(axis) != AXIS_STALLED) {
        pos = tmc2209_tstep_result();
        itoa(pos, buff, 10);
        buff[strlen(buff)] = '\n';
        serial_write(hal->serial, USART1, (uint8_t *) buff, strlen(buff));
    }
    pos = stepdir_get_pos(stepdir);
    itoa(
            pos, buff,
            10);
    buff[
            strlen(buff)
    ] = '\n';
    serial_write(
            hal
                    ->serial, USART1, (uint8_t *) buff,
            strlen(buff)
    );
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
            .en_pin=LL_GPIO_PIN_1,
            .step_pin=LL_GPIO_PIN_4,
            .dir_pin=LL_GPIO_PIN_5,
            .inverse_dir=true,
            .limit_pin=LL_GPIO_PIN_0
    };
    timer_start_microsecond_timer(hal->timer, TIM1);
    stepper = tmc2209_stepper_create(&p);

    stepdir = stepdir_create(
            stepper, STEPDIR_FREQ, STEPDIR_FREQ, axis_stall_handler);
    axis    = axis_create(stepdir);
    serial_open(hal->serial, USART1);
    UNITY_BEGIN();
    RUN_TEST(test_stops_at_max);
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