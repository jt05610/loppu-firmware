//
// Created by Jonathan Taylor on 4/24/22.
//
#include "sized_array.h"
#include "fake_timer.h"

#define MAX_INTERRUPTS 10
static struct fake_timer_t
{
    Timer       base;
    time_amount_t   microseconds;
    time_amount_t   milliseconds;
    interrupt_t interrupts[MAX_INTERRUPTS];
    uint8_t     n_interrupts;
    uint32_t    interrupt_period;
} self = {0};

static void
delay()
{

}

static time_amount_t
micros()
{
    return self.microseconds;
}

static time_amount_t
millis()
{
    return self.milliseconds;
}

static timer_interface_t fake_timer_interface = {
        .delay=delay,
        .delay_micros=delay,
        .micros=micros,
        .millis=millis
};

void
fake_timer_create(Timer base)
{
    base->vtable          = &fake_timer_interface;
    self.base             = base;
    self.microseconds     = 0;
    self.milliseconds     = 0;
    self.n_interrupts     = 0;
    self.interrupt_period = 0;
}

void
fake_timer_set_millis(time_amount_t ms)
{
    self.milliseconds = ms;
}

void
fake_timer_set_micros(time_amount_t us)
{
    self.microseconds = us;
}

void
fake_timer_register_interrupt(interrupt_t interrupt)
{
    if (MAX_INTERRUPTS > self.n_interrupts)
        self.interrupts[self.n_interrupts++] = interrupt;
}

void fake_timer_set_interrupt_period(time_amount_t us)
{
    self.interrupt_period = us;
}

void
fake_timer_run_interrupts(void)
{
    for (uint8_t i = 0; i < self.n_interrupts; i++)
        self.interrupts[i]();
}

void
fake_timer_run_for_millis(time_amount_t millis)
{
    uint32_t last_interrupt = self.microseconds;
    uint32_t last_millis    = last_interrupt;
    uint32_t target = self.milliseconds + millis;
    while (self.milliseconds < target)
    {
        self.microseconds++;
        if (self.microseconds - last_millis >= 1000)
        {
            self.milliseconds++;
            last_millis += 1000;
        }
        if (self.microseconds - last_interrupt >= self.interrupt_period)
        {
            fake_timer_run_interrupts();
            last_interrupt = self.microseconds;
        }
    }
}

