//
// Created by Jonathan Taylor on 4/21/22.
//

#include "timer.h"

void timer_delay(Timer self, time_amount_t milliseconds)
{
    if (self && self->vtable && self->vtable->delay)
        self->vtable->delay(milliseconds);
}

void timer_delay_micros(Timer self, time_amount_t microseconds)
{
    if (self && self->vtable && self->vtable->delay_micros)
        self->vtable->delay_micros(microseconds);
}

time_amount_t timer_micros(Timer self)
{
    if (self && self->vtable && self->vtable->micros)
        return self->vtable->micros();
    else
        return 0;
}

time_amount_t timer_millis(Timer self)
{
    if (self && self->vtable && self->vtable->millis)
        return self->vtable->millis();
    else
        return 0;
}

void timer_set_pwm_freq(Timer self, uint32_t freq)
{
    if (self && self->vtable && self->vtable->set_pwm_freq)
        self->vtable->set_pwm_freq(freq);
}

void timer_start_pwm(Timer self)
{
    if (self && self->vtable && self->vtable->start_pwm)
        self->vtable->start_pwm();
}
void timer_stop_pwm(Timer self)
{
    if (self && self->vtable && self->vtable->stop_pwm)
        self->vtable->stop_pwm();

}