//
// Created by Jonathan Taylor on 4/21/22.
//

#include "timer/timer.h"

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