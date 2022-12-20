/**
  ******************************************************************************
  * @file   timer.c
  * @author Jonathan Taylor
  * @date   12/13/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <stddef.h>
#include "stm32_timer.h"
#include "stm32g0xx_ll_tim.h"

static timer_base_t self = {0};

static inline void start(void * timer_instance, uint32_t freq);

static inline void stop(void * timer_instance);

static inline uint32_t get_tick(void * timer_instance);

static inline void start_us_timer(void * timer_instance);

static inline void stop_us_timer(void * timer_instance);

static inline void delay(uint32_t millis);

static inline void delay_micros(uint32_t micros);

static inline uint32_t micros();

static inline uint32_t millis();

static inline void set_pwm_freq(void * timer_instance, uint32_t freq_Hz);

static inline void
set_pwm_duty_cycle(void * timer_instance, uint16_t duty_cycle);

static inline void set_pwm_callback(PeriodicCallback cb, void * data);

static inline void
start_pwm(void * instance, uint32_t freq, uint16_t duty_cycle);

static inline void stop_pwm(void * instance);

static timer_interface_t interface = {
        .start=start,
        .stop=stop,
        .get_tick=get_tick,
        .start_us_timer=start_us_timer,
        .stop_us_timer=stop_us_timer,
        .delay=delay,
        .delay_micros=delay_micros,
        .micros=micros,
        .millis=millis,
        .set_pwm_freq=set_pwm_freq,
        .set_pwm_duty_cycle=set_pwm_duty_cycle,
        .set_pwm_callback=set_pwm_callback,
        .start_pwm=start_pwm,
        .stop_pwm=stop_pwm
};

Timer
stm32_timer_create()
{
    self.vtable = &interface;
    return &self;
}

static inline void
start(void * timer_instance, uint32_t freq)
{

}

static inline void
stop(void * timer_instance)
{

}

static inline uint32_t
get_tick(void * timer_instance)
{

}

static inline void
start_us_timer(void * timer_instance)
{

}

static inline void
stop_us_timer(void * timer_instance)
{

}

static inline void
delay(uint32_t millis)
{

}

static inline void
delay_micros(uint32_t micros)
{

}

static inline uint32_t
micros()
{

}

static inline uint32_t
millis()
{

}

static inline void
set_pwm_freq(void * timer_instance, uint32_t freq_Hz)
{

}

static inline void
set_pwm_duty_cycle(void * timer_instance, uint16_t duty_cycle)
{

}

static inline void
set_pwm_callback(PeriodicCallback cb, void * data)
{

}

static inline void
start_pwm(void * instance, uint32_t freq, uint16_t duty_cycle)
{

}

static inline void
stop_pwm(void * instance)
{

}

