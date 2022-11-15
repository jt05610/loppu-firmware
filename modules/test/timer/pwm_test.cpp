//
// Created by Jonathan Taylor on 4/28/22.
//
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "timer/pwm.h"
}

TEST_GROUP(PWM)
{
    void setup() override
    {
    }

    void teardown() override
    {
    }
};

TEST(PWM, calculate_prescaler)
{
    uint32_t in_clock  = 16000000;
    uint32_t out_clock = 1000000;
    uint16_t expected  = 15;
    uint16_t actual    = calculate_prescaler(in_clock, out_clock);
    LONGS_EQUAL(expected, actual);
}

TEST(PWM, calculate_period)
{
    uint32_t in_clock = 16000000;
    uint16_t psc      = 16 - 1;
    uint16_t freq     = 100;
    uint32_t expected = 9999;
    uint32_t actual   = calculate_period(in_clock, psc, freq);
    LONGS_EQUAL(expected, actual);
}

TEST(PWM, calculate_pulse)
{
    uint16_t period     = 999;
    uint8_t  duty_cycle = 50;
    uint16_t expected   = 499;
    uint16_t actual     = calculate_pulse(period, duty_cycle);
    LONGS_EQUAL(expected, actual);
}