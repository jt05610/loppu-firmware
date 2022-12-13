//
// Created by Jonathan Taylor on 4/21/22.
//

#ifndef VALVECONTROLLER_TIMESERVICE_H
#define VALVECONTROLLER_TIMESERVICE_H

#include <stdint.h>

typedef struct timer_t           * Timer;
typedef struct timer_interface_t * TimerInterface;

/**
 * @brief delays for a millisecond period if a microsecond timer is enabled
 * @param self Timer instance
 * @param milliseconds delay in milliseconds
 */
void timer_delay(Timer self, uint32_t milliseconds);

void timer_delay_micros(Timer self, uint32_t microseconds);

uint32_t timer_get_tick(Timer self);

uint32_t timer_micros(Timer self);

uint32_t timer_millis(Timer self);

void timer_set_pwm_freq(Timer self, uint32_t freq);

void timer_set_pwm_duty_cycle(Timer self, uint16_t duty_cycle);

void timer_set_pwm_callback(Timer self, void (*cb)(void *), void *data);

void timer_start_pwm(Timer self);

void timer_stop_pwm(Timer self);

void timer_start_microsecond_timer(Timer self, void * timer_instance);

#include "timer_private.h"

#endif //VALVECONTROLLER_TIMESERVICE_H
