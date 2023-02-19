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

#include "stepper.h"
#include "stepdir.h"
#include "ic/tmc2209_stepper.h"
#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_gpio.h"
#include "bootstrap.h"
#include "unity.h"

static volatile Peripherals hal;
static Stepper              stepper;
static StepDir              stepdir;

static struct
{
    bool expecting_stall;

} tst = {0};

static inline void get_spinning();

static inline void stall_cb();

void
setUp()
{
    stepdir = stepdir_create(stepper, STEPDIR_FREQ, STEPDIR_FREQ, stall_cb);
    stepper_set_enabled(stepper, true);
}

void
tearDown()
{
    stepper_set_enabled(stepper, false);
    timer_stop(hal->timer, TIM2);
    stepdir_destroy(stepdir);
}

void
test_rotate()
{

    int32_t target = 256 * 200;
    int32_t actual;
    stepdir_rotate(stepdir, STEPDIR_MAX_VELOCITY);
    actual = stepdir_get_pos(stepdir);
    while (actual < target) {
        actual = stepdir_get_pos(stepdir);
    }
}

void
test_stop_now()
{
    get_spinning();
    int32_t expected = stepdir_get_pos(stepdir);
    stepdir_stop(stepdir, STEPDIR_STOP_NOW);
    timer_delay(hal->timer, 100);
    int32_t actual = stepdir_get_pos(stepdir);
    TEST_ASSERT_TRUE(expected <= actual + 3);
    TEST_ASSERT_TRUE(expected >= actual - 3);
}

void
test_stop_normal()
{
    get_spinning();
    int32_t expected = stepdir_get_pos(stepdir);
    stepdir_stop(stepdir, STEPDIR_STOP_NORMAL);
    timer_delay(hal->timer, 400);
    int32_t actual = stepdir_get_pos(stepdir);
    TEST_ASSERT_NOT_EQUAL(expected, actual);
}

void
test_move_to()
{
    int32_t expected = -20000;
    stepdir_move_to(stepdir, expected);
    while (stepdir_get_pos(stepdir) != expected);
    timer_delay(hal->timer, 400);
    while (0 != stepdir_get_vel(stepdir));
}

void
test_move_rel()
{
    int32_t actual;
    int32_t nudge    = 1000;
    int32_t expected = nudge;

    for (uint8_t i = 0; i < 5; i++) {
        stepdir_move_rel(stepdir, nudge);
        while (stepdir_get_pos(stepdir) != stepdir_get_target_pos(stepdir));
        actual = stepdir_get_pos(stepdir);
        TEST_ASSERT_EQUAL(expected, actual);
        expected += nudge;
    }
}

#define GETTER_TEST(name, var, expect)          \
void name##_setup();                            \
void name()                 {                   \
name##_setup();                                 \
int16_t actual = stepdir_get_##var(stepdir);    \
TEST_ASSERT_EQUAL((expect), actual);            \
}                                               \
void name##_setup()


#define SET_GET_TEST(name, var, value)          \
GETTER_TEST(name, var, value)                   \
{                                               \
    stepdir_set_##var(stepdir, value);          \
}


GETTER_TEST(test_set_get_target_pos, target_pos, 1234)
{
    stepdir_move_to(stepdir, 1234);
}


GETTER_TEST(test_get_status, target_pos, 0x00)
{}

SET_GET_TEST(test_set_get_pos, pos, 0x00)

SET_GET_TEST(test_set_get_vel_max, vel_max, 2000)

SET_GET_TEST(test_accel, accel, 5000)

SET_GET_TEST(test_set_get_freq, freq, 1000)

SET_GET_TEST(test_set_get_precision, precision, 10000)

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
            .inverse_dir=false,
            .limit_pin=LL_GPIO_PIN_0
    };
    serial_open(hal->serial, USART1);
    timer_start_microsecond_timer(hal->timer, TIM1);
    stepper = tmc2209_stepper_create(&p);

    RUN_TEST(test_set_get_pos);
    RUN_TEST(test_set_get_vel_max);
    RUN_TEST(test_accel);
    RUN_TEST(test_set_get_freq);
    RUN_TEST(test_set_get_precision);
    RUN_TEST(test_get_status);
    RUN_TEST(test_set_get_target_pos);
    RUN_TEST(test_move_rel);
    RUN_TEST(test_move_to);
    RUN_TEST(test_stop_normal);
    RUN_TEST(test_stop_now);
    RUN_TEST(test_rotate);
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

static inline void
stall_cb()
{
    if (!tst.expecting_stall) {
        TEST_FAIL();
    } else {
        TEST_PASS();
    }
}

static inline void
get_spinning()
{
    stepdir_rotate(stepdir, STEPDIR_MAX_VELOCITY);
    while (stepdir_get_pos(stepdir) < 256 * 100);
}
