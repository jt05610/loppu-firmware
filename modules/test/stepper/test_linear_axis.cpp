/**
  ******************************************************************************
  * @file   test_linear_axis.cpp
  * @author Jonathan Taylor
  * @date   11/16/22
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
#include "fake_gpio.h"
#include "fake_stepper.h"
#include "stepper/stepper_controller.h"
#include "stepper/linear_axis.h"
}

TEST_GROUP(linear_axis)
{
    gpio_t fake_gpio;
    stepper_t        stepper;
    stepper_controller_t controller;
    linear_axis_t axis;
    void setup() override
    {
        fake_gpio_create(&fake_gpio);
        fake_stepper_create(&stepper, &fake_gpio);
        controller.stepper = &stepper;
        stepper_controller_create(&controller, 1000);
        linear_axis_create(&axis, &controller, 200 * 25);
    }

    void teardown() override
    {
    }
};

TEST(linear_axis, home_interrupt)
{
    linear_axis_home_interrupt(&axis);
    CHECK_EQUAL(AXIS_HOME_TRIGGERED, axis.state);
}

TEST(linear_axis, idle_new_position)
{
    axis.state = AXIS_IDLE;
    axis.new_position = true;
    axis.target = 0.01;
    axis.velocity = .1;
    linear_axis_update(&axis);
    CHECK_EQUAL(axis.target * 200 * 25, controller.target.position);
    CHECK_EQUAL(axis.velocity * 200 * 25, controller.target.velocity);
}

TEST(linear_axis, moving)
{

}
TEST(linear_axis, home_triggered)
{

}

TEST(linear_axis, disabled)
{

}
TEST(linear_axis, go_to)
{

}

TEST(linear_axis, enable)
{

}

TEST(linear_axis, disable)
{

}

TEST(linear_axis, home)
{

}

TEST(linear_axis, set_steps_per_mm)
{

}

TEST(linear_axis, set_accel)
{

}

TEST(linear_axis, current_position)
{

}