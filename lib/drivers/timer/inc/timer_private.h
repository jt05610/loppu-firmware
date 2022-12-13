//
// Created by Jonathan Taylor on 4/24/22.
//

#ifndef VALVECONTROLLER_TIMESERVICEPRIVATE_H
#define VALVECONTROLLER_TIMESERVICEPRIVATE_H

#include "timer.h"

typedef struct timer_interface_t
{
    void (* delay)(uint32_t millis);

    void (* delay_micros)(uint32_t micros);

    uint32_t (* micros)();

    uint32_t (* millis)();

    void (* set_pwm_freq)(uint32_t freq_Hz);

    void (* set_pwm_duty_cycle)(uint16_t duty_cycle);

    void (*start_pwm)();

    void (*stop_pwm)();

} timer_interface_t;

typedef struct timer_t
{
    TimerInterface vtable;
} timer_t;

#endif //VALVECONTROLLER_TIMESERVICEPRIVATE_H
