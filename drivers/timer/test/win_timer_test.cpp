//
// Created by taylojon on 7/26/2022.
//
#ifdef WIN32
#include "CppUTest/TestHarness.h"
extern "C"
{
#include "timer/win_timer.h"
}

TEST_GROUP(win_timer)
{
    timer_t time;
    void setup() override
    {
        win_timer_create(&time);
    }

    void teardown() override
    {
    }
};

TEST(win_timer, create)
{
    CHECK_TRUE(win_timer_freq());
}

TEST(win_timer, Micros)
{
    const int64_t n = 10;
    int64_t sum = 0;
    int64_t timer_start;
    uint64_t cal_timer_start;
    uint64_t current;
    for (uint8_t i = 0; i < n; i ++)
    {
        cal_timer_start = win_time_stamp() / 10;
        current = win_time_stamp() / 10;
        timer_start = timer_micros(&time);
        while( current - cal_timer_start < 1000)
            current = (win_time_stamp() / 10);
        sum += (timer_micros(&time) - timer_start);
    }
    CHECK_TRUE((sum / 10) < 1002 && (sum / 10) >998);
}

TEST(win_timer, Millis)
{
    const int64_t n = 10;
    int64_t sum = 0;
    int64_t timer_start;
    uint64_t cal_timer_start;
    uint64_t current;
    for (uint8_t i = 0; i < n; i ++)
    {
        cal_timer_start = win_time_stamp() / 10000;
        current = win_time_stamp() / 10000;
        timer_start = timer_millis(&time);
        while( current - cal_timer_start < 10)
            current = (win_time_stamp() / 10000);
        sum += (timer_millis(&time) - timer_start);
    }
    uint64_t res = sum / 10;
    CHECK_TRUE(9 <= res && res <= 11);
}

TEST(win_timer, Delay)
{
    const int64_t n = 10;
    uint64_t sum = 0;
    uint64_t cal_timer_start;
    uint64_t current;
    for (uint8_t i = 0; i < n; i ++)
    {
        cal_timer_start = win_time_stamp() / 10000;
        timer_delay(&time, 10);
        current = win_time_stamp() / 10000;
        sum += (current - cal_timer_start);
    }
    uint64_t res = sum / 10;
    CHECK_TRUE(9 <= res && res <= 11);
}

TEST(win_timer, DelayMicros)
{
    const int64_t n = 10;
    uint64_t sum = 0;
    uint64_t cal_timer_start;
    uint64_t current;
    for (uint8_t i = 0; i < n; i ++)
    {
        cal_timer_start = win_time_stamp() / 10;
        timer_delay_micros(&time, 1000);
        current = win_time_stamp() / 10;
        sum += (current - cal_timer_start);
    }
    uint64_t res = sum / 10;
    CHECK_TRUE(999 <= res && res <= 1001);

}
#endif