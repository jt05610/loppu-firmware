#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
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
#include <iostream>
#include <chrono>

extern "C"
{
#include "buttons/buttons.h"
}

buttons_t buttons;

typedef struct {
    uint8_t flag;
    uint8_t expected_state;
} test_case_t;

TEST_GROUP(buttons)
{

    void setup() override
    {
        buttons_create(&buttons, 0x03, 0x02);
    }

    void teardown() override
    {

    }

    static void run_test(void (*func)(Buttons self, uint8_t flag), test_case_t * test_case, uint64_t n_trials)
    {
        typedef std::chrono::high_resolution_clock clock;
        using std::chrono::nanoseconds;
        using std::chrono::duration_cast;
        uint64_t results[n_trials];
        for (uint64_t i = 0; i < n_trials; i ++)
        {
            auto t0 = clock::now();
            func(&buttons, test_case->flag);
            auto t1 = clock::now();
            results[i] = duration_cast<nanoseconds>(t1-t0).count();
        }
        uint64_t sum = 0;
        for (auto result: results)
            sum += result;
        printf("Average (ns): %llu\n", sum / n_trials);
        CHECK_EQUAL(test_case->expected_state, buttons.state);
    }
};

test_case_t cases[] = {
        {0x01, 0x01},
        {0x02, 0x03},
        {0x04, 0x02},
        {0x08, 0x00},
};

TEST(buttons, handle)
{
    for (auto c: cases)
        run_test(buttons_handle, &c, 10000);
}

#pragma clang diagnostic pop