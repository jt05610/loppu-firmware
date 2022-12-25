/**
  ******************************************************************************
  * @file   test_timer.h
  * @author Jonathan Taylor
  * @date   12/23/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_TEST_TIMER_H
#define INJECTOR_TEST_TIMER_H

#include "timer.h"

void setup_timer(Timer timer, void * instance);

int run_all_tests();

void test_start();

void test_stop();

void test_start_us_timer();

void test_stop_us_timer();

void test_delay();

void test_delay_micros();

void test_micros();

void test_millis();

void test_set_pwm_freq();

void test_set_pwm_period();

void set_pwm_duty_cycle();

void test_set_pwm_callback();

void test_start_pwm();

void test_stop_pwm();


#endif //INJECTOR_TEST_TIMER_H
