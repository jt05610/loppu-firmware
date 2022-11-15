//
// Created by Jonathan Taylor on 4/28/22.
//

#ifndef MIXINGVALVECONTROLLER_PWMPRIVATE_H
#define MIXINGVALVECONTROLLER_PWMPRIVATE_H

#include "timer/pwm.h"


typedef struct timer_param_t
{
    uint32_t period;
    uint32_t pulse;
    uint32_t prescaler;
} timer_param_t;

typedef struct pwm_interface_t
{
    void (* set_period)(PWM, uint32_t period);

    void (* set_pulse)(PWM, uint32_t pulse);

    void (* set_prescaler)(PWM, uint32_t prescaler);

    pwm_timer_state_t (* read_state)(void);

    void (* register_callback)(pwm_callback_t *);

    void (* run_callbacks)(void);
} pwm_interface_t;

typedef struct pwm_t
{
    PWMInterface vtable;
    timer_param_t * params;
    pwm_instance_t instance;
} pwm_t;

#endif //MIXINGVALVECONTROLLER_PWMPRIVATE_H
