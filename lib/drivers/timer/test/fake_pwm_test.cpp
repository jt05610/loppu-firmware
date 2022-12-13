//
// Created by Jonathan Taylor on 4/28/22.
//
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "fake_pwm.h"
}

const uint8_t  timerCount = 2;
static uint8_t timesCalled[timerCount];

void incrementTimesCalled(uint8_t id);

TEST_GROUP(FakePWM)
{
    pwm_t         pwm[3];
    timer_param_t params[3];

    void setup() override
    {
        for (auto &p: params)
            p = {8, 4, 1};

        for (uint8_t i = 0; i < 3; i++)
            fake_pwm_create(&pwm[i], &params[i]);

        timesCalled[0] = 0;
        timesCalled[1] = 0;
    }

    void teardown() override
    {
        fake_pwm_reset();
    }
};

void incrementTimesCalled(uint8_t id)
{
    timesCalled[id]++;
}

void incrementFirst()
{
    incrementTimesCalled(0);
}

TEST(FakePWM, create)
{
    LONGS_EQUAL(3, fake_pwm_get_n_instances());
}

TEST(FakePWM, ReadCounter)
{
    LONGS_EQUAL(0, fake_pwm_read_counter(&pwm[0]));
}

TEST(FakePWM, SetCounter)
{
    fake_pwm_set_counter(&pwm[0], 42);
    LONGS_EQUAL(42, fake_pwm_read_counter(&pwm[0]));
}

TEST(FakePWM, IncrementCounter)
{
    fake_pwm_increment_counter(&pwm[0]);
    LONGS_EQUAL(1, fake_pwm_read_counter(&pwm[0]));
}


TEST(FakePWM, CounterRollsOver)
{
    fake_pwm_set_counter(&pwm[0], 0xfffe);
    LONGS_EQUAL(0xfffe, fake_pwm_read_counter(&pwm[0]));
    fake_pwm_increment_counter(&pwm[0]);
    LONGS_EQUAL(0xffff, fake_pwm_read_counter(&pwm[0]));
    fake_pwm_increment_counter(&pwm[0]);
    LONGS_EQUAL(0, fake_pwm_read_counter(&pwm[0]));
}

TEST(FakePWM, read_timer_state)
{
    LONGS_EQUAL(Active, fake_pwm_timer_state(&pwm[0]));
    fake_pwm_set_counter(&pwm[0], 4);
    LONGS_EQUAL(Inactive, fake_pwm_timer_state(&pwm[0]));
    fake_pwm_set_counter(&pwm[0], 8);
    LONGS_EQUAL(Active, fake_pwm_timer_state(&pwm[0]));
}

TEST(FakePWM, ReadState)
{
    LONGS_EQUAL(0x7, pwm_read_state(pwm));
    for (auto &i: pwm)
        fake_pwm_set_counter(&i, 4);
    LONGS_EQUAL(0x0, pwm_read_state(pwm));
}

TEST(FakePWM, set_period)
{
    pwm_set_period(&pwm[0], 0xFEED);
    LONGS_EQUAL(0xFEED, pwm[0].params->period);
}

TEST(FakePWM, set_pulse)
{
    pwm_set_period(&pwm[0], 0xFEED);
    pwm_set_pulse(&pwm[0], 0xBEEF);
    LONGS_EQUAL(0xBEEF, pwm[0].params->pulse);
}

TEST(FakePWM, set_prescaler)
{
    pwm_set_period(&pwm[0], 0xFEED);
    pwm_set_prescaler(&pwm[0], 0xBEEF);
    LONGS_EQUAL(0xBEEF, pwm[0].params->prescaler);
}

TEST(FakePWM, SetParametersUnhappyParams)
{
    pwm_set_pulse(&pwm[0], 0xBEEF);
    LONGS_EQUAL(4, pwm[0].params->pulse);
}

TEST(FakePWM, RegisterCallback)
{
    pwm_callback_t callback;
    callback.on     = 0x01;
    callback.action = incrementFirst;
    pwm_register_callback(pwm, &callback);
    LONGS_EQUAL(1, fake_pwm_n_callbacks());
    LONGS_EQUAL(0x01, fake_pwm_get_callback(0)->on);
}

TEST(FakePWM, RunCallbacks)
{
    pwm_callback_t callback;
    callback.on     = 0x07;
    callback.action = incrementFirst;
    pwm_register_callback(pwm, &callback);
    for (uint8_t i = 0; i < 8; i++)
    {
        for (auto &p: pwm)
            fake_pwm_increment_counter(&p);
        pwm_run_callbacks(pwm);
    }
    LONGS_EQUAL(2, timesCalled[0]);
}

uint8_t bitShift(uint8_t input)
{
    return (input & 0x1) | ((input >> (input & 0x1)) & 0x2);
}

TEST(FakePWM, BitShift)
{
    uint8_t      inputs[]          = {
            0x0,
            0x4,
            0x2,
            0x6,
            0x1,
            0x5,
            0x3,
            0x7
    };
    uint8_t      expectedOutputs[] = {
            0x0,
            0x0,
            0x2,
            0x2,
            0x1,
            0x3,
            0x1,
            0x3,
    };
    for (uint8_t i                 = 0; i < 8; i++)
    {
        LONGS_EQUAL(expectedOutputs[i], bitShift(inputs[i]));
    }
}