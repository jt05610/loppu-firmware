//
// Created by Jonathan Taylor on 4/28/22.
//

#ifndef MIXINGVALVECONTROLLER_PWM_H
#define MIXINGVALVECONTROLLER_PWM_H

#include "project_types.h"
#include "timer/timer_math.h"

typedef struct pwm_t           * PWM;
typedef struct pwm_interface_t * PWMInterface;
typedef struct timer_param_t   * PWMTimerParameters;
typedef struct pwm_timer_t     * PWM_Timer;

typedef uint8_t pwm_timer_state_t;

typedef uint8_t pwm_instance_t;

typedef struct pwm_callback_t
{
    pwm_timer_state_t on;

    void (* action)(void);
} pwm_callback_t;

typedef enum pwm_single_timer_state_t
{
    Inactive = 0x0,
    Active   = 0x1,
} pwm_single_timer_state_t;

pwm_timer_state_t pwm_read_state(PWM pwm);

void pwm_set_period(PWM pwm, uint16_t period);

void pwm_set_pulse(PWM pwm, uint16_t pulse);

void pwm_set_prescaler(PWM pwm, uint16_t prescaler);

void pwm_register_callback(PWM pwm, pwm_callback_t * callback);

void pwm_run_callbacks(PWM pwm);

PWMTimerParameters pwm_get_params(PWM pwm);

#include "timer/.private/pwm_private.h"

#endif //MIXINGVALVECONTROLLER_PWM_H
