//
// Created by taylojon on 7/19/2022.
//

#include "CppUTest/TestHarness.h"
#include "mock_gpio.h"

extern "C"
{
#include "stepper/a4988_stepper.h"
#include "fake_timer.h"
#include "fake_pwm.h"
#include "mock_gpio_c.h"
pwm_t  pwm;
gpio_t gpio;
}

static void
pwm_callback()
{
    fake_pwm_increment_counter(&pwm);
    pwm_run_callbacks(&pwm);
}

static void
pwm_rising_callback()
{
    if (pwm.params->pulse)
        gpio_set_pin(&gpio, STEP_PORT, STEP_PIN);
}

static void
pwm_falling_callback()
{
    if (pwm.params->pulse)
        gpio_reset_pin(&gpio, STEP_PORT, STEP_PIN);
}

static pwm_callback_t rising_callback  = {0x01, pwm_rising_callback};
static pwm_callback_t falling_callback = {0x00, pwm_falling_callback};

TEST_GROUP(a4988_stepper)
{
    stepper_t             stepper;
    stepper_params_t      params;
    timer_param_t         pwm_params = {0, 0, 0};
    timer_t               time;
    static const uint32_t sys_tick   = 16000000;

    void setup() override
    {
        fake_timer_create(&time);
        fake_pwm_create(&pwm, &pwm_params);
        mock_gpio_create(&gpio);
        fake_timer_register_interrupt(a4988_us_interrupt);
        fake_timer_register_interrupt(pwm_callback);

        fake_timer_set_interrupt_period(1);
        a4988_init_t init = {
                .base=&stepper,
                .gpio=&gpio,
                .time=&time,
                .pwm=&pwm,
                .sys_tick =sys_tick
        };

        a4988_stepper_create(&init);
        pwm_register_callback(&pwm, &rising_callback);
        pwm_register_callback(&pwm, &falling_callback);
    }

    void teardown() override
    {
        params = {0, 0, 0};
        fake_pwm_reset();
        mock_gpio_check_expectations();
        mock_gpio_destroy();
    }
};

TEST(a4988_stepper, create)
{
}

TEST(a4988_stepper, full_microstep)
{
    uint32_t current = 0x01 | (0x01 << MS1_PIN);
    mock_gpio_expect_read_port(MS_PORT, current);
    mock_gpio_expect_write_port(MS_PORT, 0x01);
    a4988_set_microstep(FULL_STEP);
}

TEST(a4988_stepper, half_microstep)
{
    uint32_t expected = 0x01 << MS1_PIN;
    mock_gpio_expect_read_port(MS_PORT, 0x00);
    mock_gpio_expect_write_port(MS_PORT, expected);
    a4988_set_microstep(HALF_STEP);
}

TEST(a4988_stepper, quarter_microstep)
{
    uint32_t current  = 0x01 << MS1_PIN;
    uint32_t expected = 0x01 << MS2_PIN;
    mock_gpio_expect_read_port(MS_PORT, current);
    mock_gpio_expect_write_port(MS_PORT, expected);
    a4988_set_microstep(QUARTER_STEP);
}

TEST(a4988_stepper, eighth_microstep)
{
    uint32_t current  = 0x01 << MS3_PIN;
    uint32_t expected = (0x01 << MS2_PIN) | (0x01 << MS1_PIN);
    mock_gpio_expect_read_port(MS_PORT, current);
    mock_gpio_expect_write_port(MS_PORT, expected);
    a4988_set_microstep(EIGHTH_STEP);
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
    a4988_set_microstep(SIXTEENTH_STEP);
}

TEST(a4988_stepper, reset)
{
    mock_gpio_expect_reset_pin(RESET_PORT, RESET_PIN);
    a4988_reset();
}

TEST(a4988_stepper, enable)
{
    mock_gpio_expect_reset_pin(ENABLE_PORT, ENABLE_PIN);
    a4988_enable();
}

TEST(a4988_stepper, sleep)
{
    mock_gpio_expect_reset_pin(SLEEP_PORT, SLEEP_PIN);
    a4988_sleep();
}

TEST(a4988_stepper, wakeup)
{
    mock_gpio_expect_set_pin(SLEEP_PORT, SLEEP_PIN);
    a4988_wakeup();
}

TEST(a4988_stepper, constant_speed)
{
    // forwards
    params.speed    = 100;
    params.position = 20;
    params.accel    = 0;
    stepper_set_target(&stepper, &params);
    mock_gpio_expect_set_pin(DIR_PORT, DIR_PIN);
    for (uint32_t i = 0; i < params.position; i++)
    {
        mock_gpio_expect_set_pin(STEP_PORT, STEP_PIN);
        mock_gpio_expect_reset_pin(STEP_PORT, STEP_PIN);
    }
    stepper_set_course(&stepper);
    fake_timer_run_for_millis(params.speed * params.position);


    params.position = 0;
    stepper_set_target(&stepper, &params);
    mock_gpio_expect_reset_pin(DIR_PORT, DIR_PIN);
    stepper_set_course(&stepper);
    for (uint32_t i = 0; i < 20; i++)
    {
        mock_gpio_expect_set_pin(STEP_PORT, STEP_PIN);
        mock_gpio_expect_reset_pin(STEP_PORT, STEP_PIN);
    }

    fake_timer_run_for_millis(20 * params.speed);
}