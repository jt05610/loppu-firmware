//
// Created by Jonathan Taylor on 4/28/22.
//

#include "timer/pwm.h"

pwm_timer_state_t
pwm_read_state(PWM pwm)
{
    if (pwm && pwm->vtable && pwm->vtable->read_state)
        return pwm->vtable->read_state();
    else
        return 0;
}

void
pwm_set_period(PWM pwm, uint16_t period)
{
    if (pwm && pwm->vtable && pwm->vtable->set_period)
        pwm->vtable->set_period(pwm, period);
}

void
pwm_set_pulse(PWM pwm, uint16_t pulse)
{
    if (pwm && pwm->vtable && pwm->vtable->set_pulse)
        pwm->vtable->set_pulse(pwm, pulse);
}

void
pwm_set_prescaler(PWM pwm, uint16_t prescaler)
{
    if (pwm && pwm->vtable && pwm->vtable->set_prescaler)
        pwm->vtable->set_prescaler(pwm, prescaler);
}

void
pwm_register_callback(PWM pwm, pwm_callback_t * callback)
{
    if (pwm && pwm->vtable && pwm->vtable->register_callback)
        pwm->vtable->register_callback(callback);
}

void
pwm_run_callbacks(PWM pwm)
{
    if (pwm && pwm->vtable && pwm->vtable->run_callbacks)
        pwm->vtable->run_callbacks();
}


PWMTimerParameters
pwm_get_params(PWM pwm)
{
    return pwm->params;
}