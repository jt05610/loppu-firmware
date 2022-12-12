/**
  ******************************************************************************
  * @file   test_stepper_controller.cpp
  * @author Jonathan Taylor
  * @date   11/15/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <cmath>
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "fake_stepper.h"
#include "stepper/stepper_controller.h"
#include "fake_gpio.h"
}

TEST_GROUP(stepper_controller)
{
    stepper_t        stepper;
    stepper_controller_t controller;
    gpio_t fake_gpio;
    void setup() override
    {
        fake_gpio_create(&fake_gpio);
        fake_stepper_create(&stepper, &fake_gpio);
        controller.stepper = &stepper;
        stepper_controller_create(&controller, 1000);
    }

    void teardown() override
    {
    }
};


TEST(stepper_controller, set_target_happy)
{
    stepper_kinematics_t target = {
            .position = 100,
            .velocity = 200,
            .acceleration = 100
    };
    stepper_controller_set_target(&controller, &target);
    stepper_kinematics_t * actual = stepper_controller_get_target(&controller);
    CHECK_EQUAL(target.position, actual->position);
    CHECK_EQUAL(target.velocity, actual->velocity);
    CHECK_EQUAL(target.acceleration, actual->acceleration);
}

TEST(stepper_controller, set_target_sad)
{
    stepper_kinematics_t target = {
            .position = 100,
            .velocity = 20000,
            .acceleration = 100
    };
    stepper_controller_set_target(&controller, &target);
    stepper_kinematics_t * actual = stepper_controller_get_target(&controller);
    CHECK_EQUAL(0, actual->position);
    CHECK_EQUAL(0, actual->velocity);
    CHECK_EQUAL(0, actual->acceleration);
}

TEST(stepper_controller, constant_velocity)
{
    stepper_kinematics_t target = {
            .position = 250,
            .velocity = 500,
            .acceleration = 0
    };
    stepper_controller_set_target(&controller, &target);
    controller.updated = true;
    stepper_update(&controller); // sets state first
    controller.updated = true;
    uint32_t period = UPDATE_FREQUENCY >> 2;
    for (uint16_t i = 0; i < period; i++) {
        stepper_update(&controller);
        controller.updated = true;
    }
    CHECK_EQUAL(125, controller.ramp.position);
    for (uint16_t i = 0; i < period; i++) {
        stepper_update(&controller);
        controller.updated = true;

    }
        stepper_update(&controller);
    CHECK_EQUAL(250, controller.ramp.position);
    target = {
            .position = 0,
            .velocity = -500,
            .acceleration = 0
    };
    stepper_controller_set_target(&controller, &target);
    stepper_update(&controller); // sets state first
    controller.updated = true;
    for (uint16_t i = 0; i < 2*period; i++) {
        stepper_update(&controller);
        controller.updated = true;
    }
    CHECK_EQUAL(0, controller.ramp.position);
}

uint32_t position_after_time(double x0, double v0, double a, double v_set, double time_ms)
{
    double t_v_set;
    time_ms = time_ms / 1000;

    // time to reach v_set
    if (a == 0) {
        t_v_set = time_ms;
        v0 = v_set;
    }
    else
        t_v_set = ((v_set - v0) / a);
    double result = x0 + (v0*t_v_set) + (0.5 * a * t_v_set * t_v_set);
    double remaining = time_ms - t_v_set;
    result += (v_set*remaining) + (0.5 * a * remaining * remaining);
    return (uint32_t)floor(result);

}

TEST(stepper_controller, pos_after_time)
{
    uint32_t actual = position_after_time(0, 100, 0, 100, 1000);
    CHECK_EQUAL(100, actual);
    actual = position_after_time(0, 0, 5, 100, 10000);
    CHECK_EQUAL(250, actual);
}

TEST(stepper_controller, constant_accel)
{
    stepper_kinematics_t target = {
            .position = 10000,
            .velocity = 500,
            .acceleration = 5
    };
    uint32_t run_time_ms = 100;
    uint32_t expected = position_after_time(0, 0, target.acceleration, target.velocity, run_time_ms);

    stepper_controller_set_target(&controller, &target);
    stepper_update(&controller); // sets state first
    uint32_t period = UPDATE_FREQUENCY * run_time_ms / 1000;
    for (uint32_t i = 0; i < period; i++) {
        stepper_update(&controller);
        controller.updated = true;
    }
    CHECK_EQUAL(expected, controller.ramp.position);
}
