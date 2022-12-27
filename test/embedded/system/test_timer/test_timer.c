/**
  ******************************************************************************
  * @file   test_timer.c
  * @author Jonathan Taylor
  * @date   12/23/22
  * @brief  Timer tests source.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "test_timer.h"
#include "unity_config.h"
#include "unity.h"
#include "stm32g0xx_ll_tim.h"
#include "adapters/stm32/config/default/rcc_config.h"

static struct
{
    Timer timer;
    void * instance;
} self = {0};

void (* tests[])() = {
        test_start,
};

void setUp()
{

}

void tearDown()
{
    LL_TIM_SetCounter()
    timer_stop(self.timer, self.instance);
}

void
test_start()
{
    timer_start(self.timer, self.instance, 16000000);
    uint32_t start = timer_get_tick(self.timer, self.instance);
    uint32_t end = timer_get_tick(self.timer, self.instance);
    TEST_ASSERT_NOT_EQUAL(start, end);
}

void
test_stop()
{
    timer_start(self.timer, self.instance, 16000000);
    timer_stop(self.timer, self.instance);
    uint32_t start = timer_get_tick(self.timer, self.instance);
    uint32_t end = timer_get_tick(self.timer, self.instance);
    TEST_ASSERT_EQUAL(start, end);
}

void
test_start_us_timer()
{
    timer_start_microsecond_timer(self.timer, self.instance);
    TEST_ASSERT_EQUAL((STM32_SYS_TICK / 1000000) - 1, LL_TIM_GetPrescaler(self.instance));
}

void
test_set_pwm_freq()
{

}

void
test_set_pwm_period()
{

}

void
set_pwm_duty_cycle()
{

}

void
test_set_pwm_callback()
{

}

void
test_start_pwm()
{

}

void
test_stop_pwm()
{

}

void
setup_timer(Timer timer, void * instance)
{
    self.timer    = timer;
    self.instance = instance;
}

int
run_all_tests()
{
    UNITY_BEGIN();
    RUN_TEST(test_start);
    RUN_TEST(test_stop);
    RUN_TEST(test_start_us_timer);
    return UNITY_END();
}
