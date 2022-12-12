//
// Created by Jonathan Taylor on 4/24/22.
//

#ifndef VALVECONTROLLER_TIMESERVICEPRIVATE_H
#define VALVECONTROLLER_TIMESERVICEPRIVATE_H

#include "../timer.h"

typedef struct timer_interface_t
{
    void (* delay)(time_amount_t millis);

    void (* delay_micros)(time_amount_t micros);

    time_amount_t (* micros)();

    time_amount_t (* millis)();

    void (* set_pwm_freq)(uint32_t freq_Hz);

    void (*start_pwm)();
    void (*stop_pwm)();

} timer_interface_t;

typedef struct timer_t
{
    TimerInterface vtable;
} timer_t;

#endif //VALVECONTROLLER_TIMESERVICEPRIVATE_H
