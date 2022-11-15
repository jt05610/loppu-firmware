//
// Created by Jonathan Taylor on 4/24/22.
//

#ifndef VALVECONTROLLER_FAKETIMESERVICE_H
#define VALVECONTROLLER_FAKETIMESERVICE_H

#include "timer/timer.h"

typedef void (* interrupt_t)(void);

void fake_timer_create(Timer base);

void fake_timer_set_millis(time_amount_t ms);

void fake_timer_set_micros(time_amount_t us);

void fake_timer_register_interrupt(interrupt_t interrupt);

void fake_timer_run_interrupts(void);

void fake_timer_set_interrupt_period(time_amount_t us);

void fake_timer_run_for_millis(time_amount_t millis);

#endif //VALVECONTROLLER_FAKETIMESERVICE_H
