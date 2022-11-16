//
// Created by taylojon on 7/19/2022.
//

#include "CppUTest/TestHarness.h"
#include "mock_gpio.h"

extern "C"
{
#include "stepper/a4988_stepper.h"
#include "mock_gpio_c.h"
}

TEST_GROUP(a4988_stepper)
{
    stepper_t             stepper;
    gpio_t gpio;
    void setup() override
    {
        mock_gpio_create(&gpio);
       a4988_init_t init = {
                .base=&stepper,
                .gpio=&gpio,
        };

        a4988_stepper_create(&init);
    }

    void teardown() override
    {
        mock_gpio_check_expectations();
        mock_gpio_destroy();
    }
};


TEST(a4988_stepper, full_microstep)
{
    uint32_t current = 0x01 | ~(0x01 << MS1_PIN);
    mock_gpio_expect_read_port(MS_PORT, current);
    mock_gpio_expect_write_port(MS_PORT, 0x01);
    stepper_set_microstep(&stepper, FULL_STEP);
}

TEST(a4988_stepper, half_microstep)
{
    uint32_t expected = 0x01 << MS1_PIN;
    mock_gpio_expect_read_port(MS_PORT, 0x00);
    mock_gpio_expect_write_port(MS_PORT, expected);
    stepper_set_microstep(&stepper, HALF_STEP);
}

TEST(a4988_stepper, quarter_microstep)
{
    uint32_t current  = 0x01 << MS1_PIN;
    uint32_t expected = 0x01 << MS2_PIN;
    mock_gpio_expect_read_port(MS_PORT, current);
    mock_gpio_expect_write_port(MS_PORT, expected);
    stepper_set_microstep(&stepper, QUARTER_STEP);
}

TEST(a4988_stepper, eighth_microstep)
{
    uint32_t current  = 0x01 << MS3_PIN;
    uint32_t expected = (0x01 << MS2_PIN) | (0x01 << MS1_PIN);
    mock_gpio_expect_read_port(MS_PORT, current);
    mock_gpio_expect_write_port(MS_PORT, expected);
    stepper_set_microstep(&stepper, EIGHTH_STEP);
}

TEST(a4988_stepper, sixteenth_microstep)
{
    uint32_t current  = 0x01;
    uint32_t expected = current
                        | (0x01 << MS3_PIN)
                        | (0x01 << MS2_PIN)
                        | (0x01 << MS1_PIN);

    mock_gpio_expect_read_port(MS_PORT, current);
    mock_gpio_expect_write_port(MS_PORT, expected);
    stepper_set_microstep(&stepper, SIXTEENTH_STEP);
}

TEST(a4988_stepper, reset)
{
    mock_gpio_expect_reset_pin(RESET_PORT, RESET_PIN);
    a4988_reset(&stepper);
}

TEST(a4988_stepper, enable)
{
    mock_gpio_expect_reset_pin(ENABLE_PORT, ENABLE_PIN);
    stepper_enable(&stepper);
}

TEST(a4988_stepper, sleep)
{
    mock_gpio_expect_reset_pin(SLEEP_PORT, SLEEP_PIN);
    a4988_sleep(&stepper);
}

TEST(a4988_stepper, wakeup)
{
    mock_gpio_expect_set_pin(SLEEP_PORT, SLEEP_PIN);
    a4988_wakeup(&stepper);
}