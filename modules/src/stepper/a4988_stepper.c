/**
  ******************************************************************************
  * @file   a4988_stepper.c
  * @author Jonathan Taylor
  * @date   7/19/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#if 0
#include "stepper/a4988_stepper.h"

#ifdef STM32G031xx
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_it.h"
#endif
static struct
{
    Stepper          base;
    GPIO             gpio;
    stepper_params_t current;
    uint32_t         steps;
    uint32_t         planned_steps;
    uint32_t         last_accel;
} self = {0};

static inline void calculate_speed();

static void run(void);

static bool
is_idle()
{
    return self.steps >= self.planned_steps;
}

static inline void
step()
{
    if (self.steps >= self.planned_steps)
    {
        pwm_set_pulse(self.base->pwm, 0);
#ifndef STM32G031xx
        pwm_set_period(self.base->pwm, 0);
#endif
        return;
    }
    if (Forward == self.current.dir)
        self.current.position++;
    else
        self.current.position--;
    self.steps++;
}


uint32_t get_position()
{
    return self.current.position;
}

#ifdef STM32G031xx

__INTERRUPT
TIM2_IRQHandler(void)
{
    LL_TIM_ClearFlag_CC2(TIM2);
    if (self.steps < self.planned_steps)
        step();
    else
    {
        LL_TIM_DisableCounter(TIM16);
        pwm_set_pulse(self.base->pwm, 0);
    }
}

__INTERRUPT
TIM16_IRQHandler(void)
{
    LL_TIM_ClearFlag_UPDATE(TIM16);
    a4988_us_interrupt();
}

#else

static pwm_callback_t callback = {0x01, step};

#endif

static inline void
set_dir(dir_t dir)
{
    if (Forward == dir)
        gpio_set_pin(self.gpio, DIR_PORT, DIR_PIN);
    else
        gpio_reset_pin(self.gpio, DIR_PORT, DIR_PIN);
}

static void
set_course()
{
    self.current.accel     = self.base->target->accel;
    if (self.base->target->speed > A4988_MAX_SPEED)
        self.current.speed = A4988_MAX_SPEED;
    else if (self.current.accel == 0)
        self.current.speed = self.base->target->speed;
    if (self.base->target->position > self.current.position)
    {
        self.current.dir = Forward;

        self.planned_steps =
                self.base->target->position - self.current.position;
    } else
    {
        self.current.dir = Backward;

        self.planned_steps =
                self.current.position - self.base->target->position;
    }
    self.steps = 0;
    set_dir(self.current.dir);
    calculate_speed();
}

static void
run(void)
{
#ifdef STM32G031xx
    LL_TIM_EnableCounter(TIM2);
#endif
}

static void
set_position(uint32_t pos)
{
    self.current.position = pos;
}

static stepper_interface_t interface = {
        .set_course=set_course,
        .run=run,
        .is_idle = is_idle,
        .set_position = set_position
};

void
a4988_stepper_create(a4988_init_t * params)
{
    self.base         = params->base;
    self.base->vtable = &interface;
    self.gpio         = params->gpio;
    self.base->time   = params->time;
    self.base->pwm    = params->pwm;
    pwm_set_prescaler(
            self.base->pwm,
            calculate_prescaler(params->sys_tick, 1000000)
    );
    self.planned_steps    = 0;
    self.steps            = 0;
    self.current.position = 0;
    self.current.speed    = 0;
#ifndef STM32G031xx
    pwm_register_callback(self.base->pwm, &callback);
#endif
}

static inline void
calculate_speed()
{
    pwm_set_period(
            self.base->pwm, calculate_period(
                    SYS_TICK, self.base->pwm->params->prescaler,
                    self.current.speed
            ));
    pwm_set_pulse(
            self.base->pwm,
            calculate_pulse(self.base->pwm->params->period, 50));

}

void
a4988_set_microstep(microstep_t microstep)
{
    switch (microstep)
    {
        case FULL_STEP:
            gpio_reset_pin(self.gpio, MS_PORT, RESET_PINS_FULL);
            break;
        case HALF_STEP:
            gpio_reset_pin(self.gpio, MS_PORT, RESET_PINS_HALF);
            gpio_set_pin(self.gpio, MS_PORT, SET_PINS_HALF);
            break;
        case QUARTER_STEP:
            gpio_reset_pin(self.gpio, MS_PORT, RESET_PINS_QUARTER);
            gpio_set_pin(self.gpio, MS_PORT, SET_PINS_QUARTER);
            break;
        case EIGHTH_STEP:
            gpio_reset_pin(self.gpio, MS_PORT, RESET_PINS_EIGHTH);
            gpio_set_pin(self.gpio, MS_PORT, SET_PINS_EIGHTH);
            break;
        case SIXTEENTH_STEP:
            gpio_set_pin(self.gpio, MS_PORT, SET_PINS_SIXTEENTH);
            break;
        default:
            break;
    }
}

void
a4988_reset()
{
    gpio_reset_pin(self.gpio, RESET_PORT, RESET_PIN);
}

void
a4988_set()
{
    gpio_set_pin(self.gpio, RESET_PORT, RESET_PIN);
}

void
a4988_enable()
{
    gpio_reset_pin(self.gpio, ENABLE_PORT, ENABLE_PIN);
}

void
a4988_disable()
{
    gpio_set_pin(self.gpio, ENABLE_PORT, ENABLE_PIN);
}

void
a4988_sleep()
{
    gpio_reset_pin(self.gpio, SLEEP_PORT, SLEEP_PIN);
}

void
a4988_wakeup()
{
    gpio_set_pin(self.gpio, SLEEP_PORT, SLEEP_PIN);
}

void
a4988_us_interrupt()
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
}
#endif