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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ic/tmc2209_stepper.h"
#include "linear_axis.h"
#include "stm32/g031xx_adapter.h"
#include "stm32g0xx_ll_tim.h"
#include "bootstrap.h"
#include "stm32g0xx_ll_gpio.h"
#include "../../../../src/modules/modbus/inc/modbus/util.h"

static Peripherals hal;
static Stepper stepper;
static StepDir stepdir;
static Axis axis;

uint16_t pos;

void setUp() {
    stepper_set_enabled(stepper, true);
}

void tearDown() {
    stepper_set_enabled(stepper, false);
}

size_t bytestr_len(uint8_t *s) {
    size_t i = 0;
    while (s[i] != 0) {
        i++;
    }
    return i;
}

void int32_to_bytestr(const int32_t val, char *s) {
    uint8_t *p = (uint8_t *) &val;
    for (size_t i = 0; i < 4; i++) {
        s[i] = p[i];
    }
}

void sprint_int32(char *s, const int32_t val) {
    for (size_t i = 0; i < 20; i++) {
        s[i] = 0;
    }
    int32_to_bytestr(val, s);
}

void print_int32(const int32_t val) {
    // write human readable value to serial
    char buff[13]; // Buffer to hold the string representation of the integer. 12 is the maximum length for int32_t.
    itoa(val, buff, 10); // Convert the integer to a string using itoa.
    axis_update(axis);
    const size_t len = strlen(buff); // Get the length of the string.
    buff[len] = '\n'; // Add a newline character to the end of the string.
    axis_update(axis);
    serial_write(hal->serial, USART1, buff, len + 1);
    axis_update(axis);
}

static volatile bool shouldPrint = false;
static volatile bool shouldRecord = false;

void setShouldPrint() {
    shouldRecord = true;
}

void
test_home() {
    timer_set_interval_ms(hal->timer, TIM17, setShouldPrint, 100);
    axis_home(axis);
    while (!axis_homed(axis)) {
        axis_update(axis);
    }
    axis_update(axis);
}

void
test_goto() {
    uint16_t max, min;
    max = 50000;
    min = 10000;
    uint16_t loops = 10;
    while (loops--) {
        axis_set_target_vel(axis, 50000);
        axis_goto(axis, max);
        pos = axis_current_pos(axis);
        axis_start(axis);
        while (!stepdir_is_moving(stepdir)) {
            axis_update(axis);
        }
        while (stepdir_is_moving(stepdir)) {
            pos = axis_current_pos(axis);
            axis_update(axis);
        }
        axis_stop(axis);
        axis_update(axis);
        axis_set_target_vel(axis, 50000);
        axis_goto(axis, min);
        axis_start(axis);
        while (!stepdir_is_moving(stepdir)) {
            axis_update(axis);
        }
        while (stepdir_is_moving(stepdir)) {
            axis_update(axis);
        }
    }
}

void
test_stops_at_max() {
    axis_forward_stall(axis);
    while (axis_state(axis) == AXIS_FORWARD_STALL) {
        axis_update(axis);
    }
    axis_update(axis);
}

int
main() {
    hal = bootstrap(stm32_dependency_injection, 0);
    tmc2209_init_t p = {
        .hal = hal,
        .tim_inst = TIM2,
        .uart_inst = USART2,
        .gpio_inst = GPIOA,
        .en_pin = LL_GPIO_PIN_8,
        .step_pin = LL_GPIO_PIN_1,
        .dir_pin = LL_GPIO_PIN_0,
        .inverse_dir = false,
        .limit_pin = LL_GPIO_PIN_5,
        .sg_thresh = 255,
        .cs_thresh = 14000,
    };
    stepper = tmc2209_stepper_create(&p);
#define STEPS_PER_REV 200
#define MM_PER_REV 72
#define STEPS_PER_MM (STEPS_PER_REV / MM_PER_REV)
#define STEPS_PER_M (STEPS_PER_MM * 1000)
    stepdir = stepdir_create(stepper, STEPDIR_FREQ, STEPDIR_FREQ);
    axis_params_t ap = {
        .steps_per_m = STEPS_PER_M,
        .ms = MS_256,
        .step_dir = stepdir,
        .max_pos = 65535,
        .max_vel = STEPDIR_MAX_VELOCITY,
        .accel = STEPDIR_MAX_ACCELERATION,
        .home_ms = MS_16,
        .home_vel = STEPDIR_MAX_VELOCITY / 16,
    };
    axis = axis_create(&ap);
    serial_open(hal->serial, USART1);
    test_home();
    axis_stop(axis);
    test_goto();
    //timer_stop_microsecond_timer(hal->timer, TIM16);
}
