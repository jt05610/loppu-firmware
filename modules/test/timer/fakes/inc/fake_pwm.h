//
// Created by Jonathan Taylor on 4/28/22.
//

#ifndef VALVECONTROLLER_FAKEPWM_H
#define VALVECONTROLLER_FAKEPWM_H

#include "timer/pwm.h"

#define MAX_FAKE_PWM_INSTANCES 5
#define MAX_CALLBACKS 8

void fake_pwm_create(PWM base, timer_param_t * params);

void fake_pwm_reset();

uint8_t fake_pwm_get_n_instances();

void fake_pwm_set_counter(PWM base, uint16_t count);

void fake_pwm_increment_counter(PWM base);

uint16_t fake_pwm_read_counter(PWM base);

pwm_single_timer_state_t fake_pwm_timer_state(PWM base);

uint8_t fake_pwm_n_callbacks();

pwm_callback_t * fake_pwm_get_callback(uint8_t n);

#endif //VALVECONTROLLER_FAKEPWM_H
