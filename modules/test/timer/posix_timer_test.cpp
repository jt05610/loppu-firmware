/**
  ******************************************************************************
  * @file   posix_timerTest.cpp
  * @author Jonathan Taylor
  * @date   7/29/22
  * @brief  Tests for posix_timer module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef WIN32
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "timer/posix_timer.h"
}

#define N 10

TEST_GROUP(posix_timer)
{
    timer_t time;
    timeval * spec;

    void setup() override
    {
        posix_timer_create(&time);
    }

    void teardown() override
    {

    }

    time_amount_t us()
    {
        spec = posix_time_stamp();
        return (spec->tv_sec * 1000000) + spec->tv_usec;
    }

    time_amount_t ms()
    {
        return us() / 1000;
    }
};

TEST(posix_timer, micros)
{
    const int64_t n   = N;
    int64_t       sum = 0;
    int64_t       timer_start;
    uint64_t      cal_timer_start;
    uint64_t      current;

    for (uint8_t i = 0; i < n; i++)
    {
        cal_timer_start = us();
        current         = us();
        timer_start     = timer_micros(&time);
        while (current - cal_timer_start < 1000)
            current     = us();
        sum += (timer_micros(&time) - timer_start);
    }
    CHECK_TRUE(999 <= (sum / n) && (sum / n) <= 1001);
}

TEST(posix_timer, millis)
{
    const int64_t n   = N;
    int64_t       sum = 0;
    int64_t       timer_start;
    uint64_t      cal_timer_start;
    uint64_t      current;

    for (uint8_t i = 0; i < n; i++)
    {
        cal_timer_start = ms();
        current         = ms();
        timer_start     = timer_millis(&time);
        while (current - cal_timer_start < 100)
            current     = ms();
        sum += (timer_millis(&time) - timer_start);
    }
    LONGS_EQUAL(100, (sum / n));
}

TEST(posix_timer, delay)
{
    const int64_t n   = N;
    uint64_t      sum = 0;
    uint64_t      cal_timer_start;
    uint64_t      current;

    for (uint8_t i = 0; i < n; i++)
    {
        cal_timer_start = ms();
        timer_delay(&time, 10);
        current = ms();
        sum += (current - cal_timer_start);
    }

    CHECK_TRUE(9 <= (sum / n) && (sum / n) <= 11);
}

TEST(posix_timer, delay_micros)
{
    const int64_t n   = N;
    uint64_t      sum = 0;
    uint64_t      cal_timer_start;
    uint64_t      current;

    for (uint8_t i = 0; i < n; i++)
    {
        cal_timer_start = us();
        timer_delay_micros(&time, 1000);
        current = us();
        sum += (current - cal_timer_start);
    }

    CHECK_TRUE(999 <= (sum / n) && (sum / n) <= 1001);
}
#endif