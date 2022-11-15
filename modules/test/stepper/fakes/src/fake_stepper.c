/**
  ******************************************************************************
  * @file   fake_stepper.c
  * @author Jonathan Taylor
  * @date   7/11/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "fake_stepper.h"
#include "fake_timer.h"
#include "fake_pwm.h"

#define SYSTEM_TICK 16000000

static struct fake_stepper
{
    Stepper          base;
    stepper_params_t current;
    timer_param_t    pwm_params;
    uint32_t         last_accel;
    uint32_t         planned_steps;
    uint32_t         steps;
} self = {0};

static inline void
fake_stepper_step()
{
    if (self.steps >= self.planned_steps)
    {
        self.pwm_params.pulse  = 0;
        self.pwm_params.period = 0;
        return;
    }
    if (Forward == self.current.dir)
        self.current.position++;
    else
        self.current.position--;
    self.steps++;
}

static void
run(void)
{

}

static bool
is_idle(void)
{
    return self.steps == self.planned_steps;
}

static pwm_callback_t callback = {0x01, fake_stepper_step};

static inline void
calculate_speed()
{
    self.pwm_params.period = calculate_period(
            SYSTEM_TICK, self.pwm_params.prescaler, self.current.speed
    );
    self.pwm_params.pulse  = calculate_pulse(self.pwm_params.period, 50);
}

static inline void
update_pwm()
{
    if (self.current.speed < self.base->target->speed)
    {
        if (timer_micros(self.base->time) - self.last_accel
            >= self.current.accel)
        {
            self.current.speed++;
            self.last_accel = timer_micros(self.base->time);
            calculate_speed();
        }
    }
    fake_pwm_increment_counter(self.base->pwm);
    pwm_run_callbacks(self.base->pwm);
}

static inline void
set_course()
{
    if (self.base->target->accel == 0)
    {
        self.current.speed = self.base->target->speed;
        self.current.accel = 0;
    } else
    {
        self.current.accel = self.base->target->accel;
    }
    if (self.base->target->position > self.current.position)
    {

        self.base->target->dir = Forward;

        self.planned_steps =
                self.base->target->position - self.current.position;
    } else
    {
        self.base->target->dir = Backward;

        self.planned_steps =
                self.current.position - self.base->target->position;
    }
    self.steps = 0;
    calculate_speed();
}

static stepper_interface_t fake_stepper_interface = {
        .set_course = set_course,
        .run = run,
        .is_idle = is_idle
};

void
fake_stepper_create(Stepper base, Timer time, PWM pwm)
{
    base->vtable = &fake_stepper_interface;
    base->pwm    = pwm;
    base->time   = time;
    fake_timer_create(time);
    self.pwm_params.prescaler = calculate_prescaler(SYSTEM_TICK, 1000000);
    fake_pwm_create(pwm, &self.pwm_params);
    pwm_register_callback(pwm, &callback);
    fake_timer_register_interrupt(update_pwm);
    fake_timer_set_interrupt_period(1);
    self.base             = base;
    self.current.speed    = 0;
    self.current.accel    = 0;
    self.current.position = 0;
    self.steps            = 0;
}

StepperParams
fake_stepper_current()
{
    return &self.current;
}

