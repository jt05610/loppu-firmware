//
// Created by taylojon on 11/16/2022.
//
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


TEST(linear_axis, create)
{
    FAIL("ok");
}
