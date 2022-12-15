//
// Created by Jonathan Taylor on 4/24/22.
//

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "fake_timer.h"
}

uint32_t times_called;

void
fake_timer_interrupt()
{
    times_called++;
}

TEST_GROUP(FakeTimeService)
{
    timer_t time;

    void setup() override
    {
        fake_timer_create(&time);
        times_called = 0;
        fake_timer_register_interrupt(fake_timer_interrupt);
    }

    void teardown() override
    {
    }
};

TEST(FakeTimeService, Micros)
{
    fake_timer_set_micros(69);
    LONGS_EQUAL(69, timer_micros(&time));
}

TEST(FakeTimeService, Millis)
{
    fake_timer_set_millis(42);
    LONGS_EQUAL(42, timer_millis(&time));
}

TEST(FakeTimeService, Delay)
{
    timer_delay(&time, 1);
}

TEST(FakeTimeService, DelayMicros)
{
    timer_delay_micros(&time, 1);
}

TEST(FakeTimeService, run_interrupts)
{
    fake_timer_run_interrupts();
    LONGS_EQUAL(1, times_called);
}

TEST(FakeTimeService, run_for_millis)
{
    fake_timer_run_for_millis(1000);
    LONGS_EQUAL(1000, timer_millis(&time));
    LONGS_EQUAL(1000000, timer_micros(&time));
}

TEST(FakeTimeService, run_with_interrupts)
{
    fake_timer_set_interrupt_period(1000);
    fake_timer_run_for_millis(1000);
    LONGS_EQUAL(1000, times_called);
}