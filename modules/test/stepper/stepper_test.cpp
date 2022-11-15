/**
  ******************************************************************************
  * @file   stepperTest.cpp
  * @author Jonathan Taylor
  * @date   7/11/22
  * @brief  Tests for stepper module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "fake_stepper.h"
#include "fake_pwm.h"
#include "fake_timer.h"
}

TEST_GROUP(stepper)
{
    stepper_t        stepper;
    stepper_params_t params;
    pwm_t            pwm;
    timer_t          time;

    void setup() override
    {
        fake_stepper_create(&stepper, &time, &pwm);
    }

    void teardown() override
    {
        params = {0};
        fake_pwm_reset();
        fake_timer_set_millis(0);
        fake_timer_set_micros(0);
    }
};

TEST(stepper, Create)
{
    StepperParams current = fake_stepper_current();
    LONGS_EQUAL(0, current->position);
    LONGS_EQUAL(0, current->speed);
    LONGS_EQUAL(0, current->accel);
    LONGS_EQUAL(15, pwm_get_params(&pwm)->prescaler);
}

TEST(stepper, set_course)
{
    params.accel         = 0;
    params.speed         = 1;
    params.position      = 30000;
    stepper_set_target(&stepper, &params);
    stepper_set_course(&stepper);
    StepperParams actual = stepper_get_target(&stepper);
    LONGS_EQUAL(params.accel, actual->accel);
    LONGS_EQUAL(params.speed, actual->speed);
    LONGS_EQUAL(params.position, actual->position);
    LONGS_EQUAL(1000000 - 1, pwm_get_params(&pwm)->period);
    LONGS_EQUAL(500000 - 1, pwm_get_params(&pwm)->pulse);
}

TEST(stepper, constant_speed)
{
    params.accel      = 0;
    params.speed      = 100;
    params.position   = 200;
    uint32_t run_time = 2000;
    stepper_set_target(&stepper, &params);
    stepper_set_course(&stepper);
    fake_timer_run_for_millis(run_time);
    LONGS_EQUAL(params.position, fake_stepper_current()->position);
}

TEST(stepper, constant_accel)
{
    params.accel    = 50;
    params.speed    = 200;
    params.position = 200;
    stepper_set_target(&stepper, &params);
    stepper_set_course(&stepper);
    fake_timer_run_for_millis(1);
    LONGS_EQUAL(20, fake_stepper_current()->speed);
    fake_timer_run_for_millis(1);
    LONGS_EQUAL(40, fake_stepper_current()->speed);
    fake_timer_run_for_millis(1);
    LONGS_EQUAL(60, fake_stepper_current()->speed);
    fake_timer_run_for_millis(100);
    LONGS_EQUAL(params.speed, fake_stepper_current()->speed);
    fake_timer_run_for_millis(5000);
    LONGS_EQUAL(params.position, fake_stepper_current()->position);
}