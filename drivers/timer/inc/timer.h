//
// Created by Jonathan Taylor on 4/21/22.
//

#ifndef VALVECONTROLLER_TIMESERVICE_H
#define VALVECONTROLLER_TIMESERVICE_H

#include "../../modbus/inc/public/modbus/project_types.h"
#include "timer_math.h"

typedef struct timer_t           * Timer;
typedef struct timer_interface_t * TimerInterface;


#ifndef STM32G031xx
typedef int64_t time_amount_t;
#else
typedef uint32_t time_amount_t ;
#endif

void timer_delay(Timer self, time_amount_t milliseconds);

void timer_delay_micros(Timer self, time_amount_t microseconds);

time_amount_t timer_micros(Timer self);

time_amount_t timer_millis(Timer self);

void timer_set_pwm_freq(Timer self, uint32_t freq);

void timer_start_pwm(Timer self);
void timer_stop_pwm(Timer self);

#include ".private/timer_private.h"

#endif //VALVECONTROLLER_TIMESERVICE_H
