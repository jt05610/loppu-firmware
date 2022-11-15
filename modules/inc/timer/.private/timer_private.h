//
// Created by Jonathan Taylor on 4/24/22.
//

#ifndef VALVECONTROLLER_TIMESERVICEPRIVATE_H
#define VALVECONTROLLER_TIMESERVICEPRIVATE_H

#include "timer/timer.h"

typedef struct timer_interface_t
{
    void (* delay)(time_amount_t millis);

    void (* delay_micros)(time_amount_t micros);

    time_amount_t (* micros)();

    time_amount_t (* millis)();

} timer_interface_t;

typedef struct timer_t
{
    TimerInterface vtable;
} timer_t;

#endif //VALVECONTROLLER_TIMESERVICEPRIVATE_H
