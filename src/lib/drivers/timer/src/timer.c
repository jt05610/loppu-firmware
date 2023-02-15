/**
  ******************************************************************************
  * @file   timer.c
  * @author Jonathan Taylor
  * @date   12/13/22
  * @brief  Timer abstract library source.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "timer.h"

void
timer_start(Timer self, void * timer_instance, uint32_t freq)
{
    if (self && self->vtable && self->vtable->start) {
        self->vtable->start(timer_instance, freq);
    }
}

void
timer_stop(Timer self, void * timer_instance)
{
    if (self && self->vtable && self->vtable->stop) {
        self->vtable->stop(timer_instance);
    }
}

uint32_t
timer_get_tick(Timer self, void * timer_instance)
{
    if (self && self->vtable && self->vtable->get_tick) {
        return self->vtable->get_tick(timer_instance);
    }
    return 0;
}

void
timer_reset(Timer self, void * timer_instance)
{
    if (self && self->vtable && self->vtable->reset) {
        self->vtable->reset(timer_instance);
    }
}

void
timer_start_microsecond_timer(Timer self, void * timer_instance)
{
    if (self && self->vtable && self->vtable->start_us_timer) {
        self->vtable->start_us_timer(timer_instance);
    }
}

void
timer_stop_microsecond_timer(Timer self, void * timer_instance)
{
    if (self && self->vtable && self->vtable->stop_us_timer) {
        self->vtable->stop_us_timer(timer_instance);
    }
}

void
timer_delay_micros(Timer self, uint32_t microseconds)
{
    if (self && self->vtable && self->vtable->delay_micros) {
        self->vtable->delay_micros(microseconds);
    }
}

void
timer_delay(Timer self, uint32_t milliseconds)
{
    if (self && self->vtable && self->vtable->delay) {
        self->vtable->delay(milliseconds);
    }
}

uint32_t
timer_micros(Timer self)
{
    if (self && self->vtable && self->vtable->micros) {
        return self->vtable->micros();
    }
    return 0;
}

uint32_t
timer_millis(Timer self)
{
    if (self && self->vtable && self->vtable->millis) {
        return self->vtable->millis();
    }
    return 0;
}

void
timer_start_pwm(
        Timer self, void * pwm_instance, uint32_t freq, uint16_t duty_cycle)
{
    if (self && self->vtable && self->vtable->start_pwm) {
        self->vtable->start_pwm(pwm_instance, freq, duty_cycle);
    }

}

void
timer_stop_pwm(Timer self, void * pwm_instance)
{
    if (self && self->vtable && self->vtable->stop_pwm) {
        self->vtable->stop_pwm(pwm_instance);
    }
}

void
timer_set_pwm_freq(Timer self, void * pwm_instance, uint32_t freq)
{
    if (self && self->vtable && self->vtable->set_pwm_freq) {
        self->vtable->set_pwm_freq(pwm_instance, freq);
    }
}

void
timer_set_pwm_duty_cycle(Timer self, void * pwm_instance, uint16_t duty_cycle)
{
    if (self && self->vtable && self->vtable->set_pwm_duty_cycle) {
        self->vtable->set_pwm_duty_cycle(pwm_instance, duty_cycle);
    }
}

void
timer_set_pwm_callback(Timer self, PeriodicCallback cb, void * data)
{
    if (self && self->vtable && self->vtable->set_pwm_callback) {
        self->vtable->set_pwm_callback(cb, data);
    }
}

void
timer_set_pwm_period(Timer self, void * pwm_instance, uint32_t period)
{
    if (self && self->vtable && self->vtable->set_pwm_period) {
        self->vtable->set_pwm_period(pwm_instance, period);
    }
}

void
timer_register_update_callback(Timer self, void * timer_instance, void (* cb)())
{
    if (self && self->vtable && self->vtable->reg_update_callback) {
        self->vtable->reg_update_callback(timer_instance, cb);
    }
}

void
timer_register_pwm_callback(Timer self, void * timer_instance, void (* cb)())
{
    if (self && self->vtable && self->vtable->reg_pwm_callback) {
        self->vtable->reg_pwm_callback(timer_instance, cb);
    }
}

void timer_set_timeout(Timer self, void * timer_instance, uint32_t timeout)
{
    if (self && self->vtable && self->vtable->set_timeout) {
        self->vtable->set_timeout(timer_instance, timeout);
    }
}

void timer_reg_periodic_job(
        Timer self, void * timer_instance, void (* job)(void), uint32_t freq)
{

    if (self && self->vtable && self->vtable->reg_periodic_job) {
        self->vtable->reg_periodic_job(timer_instance, job, freq);
    }
}
