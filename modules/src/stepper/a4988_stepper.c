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
#include "stepper/a4988_stepper.h"

static inline void
set_dir(Stepper base, dir_t dir)
{
    if (Forward == dir)
        gpio_set_pin(base->gpio, DIR_PORT, DIR_PIN);
    else
        gpio_reset_pin(base->gpio, DIR_PORT, DIR_PIN);
}

static inline void
a4988_set_microstep(Stepper base, microstep_t microstep)
{
    switch (microstep)
    {
        case FULL_STEP:
            gpio_reset_pin(base->gpio, MS_PORT, RESET_PINS_FULL);
            break;
        case HALF_STEP:
            gpio_reset_pin(base->gpio, MS_PORT, RESET_PINS_HALF);
            gpio_set_pin(base->gpio, MS_PORT, SET_PINS_HALF);
            break;
        case QUARTER_STEP:
            gpio_reset_pin(base->gpio, MS_PORT, RESET_PINS_QUARTER);
            gpio_set_pin(base->gpio, MS_PORT, SET_PINS_QUARTER);
            break;
        case EIGHTH_STEP:
            gpio_reset_pin(base->gpio, MS_PORT, RESET_PINS_EIGHTH);
            gpio_set_pin(base->gpio, MS_PORT, SET_PINS_EIGHTH);
            break;
        case SIXTEENTH_STEP:
            gpio_set_pin(base->gpio, MS_PORT, SET_PINS_SIXTEENTH);
            break;
        default:
            break;
    }
}

static inline void
step(Stepper base)
{
    gpio_toggle(base->gpio, STEP_PORT, STEP_PIN);
}

static inline void
enable(Stepper base)
{
    gpio_reset_pin(base->gpio, ENABLE_PORT, ENABLE_PIN);
}

static inline void
disable(Stepper base)
{
    gpio_set_pin(base->gpio, ENABLE_PORT, ENABLE_PIN);
}

static stepper_interface_t interface = {
        .step = step,
        .set_dir = set_dir,
        .set_microstep = a4988_set_microstep,
        .enable = enable,
        .disable = disable
};

void
a4988_stepper_create(a4988_init_t * params)
{
    params->base         = params->base;
    params->base->vtable = &interface;
    params->base->gpio   = params->gpio;
}

void a4988_reset(Stepper base)
{
    gpio_reset_pin(base->gpio, RESET_PORT, RESET_PIN);

}
void a4988_set(Stepper base)
{
    gpio_set_pin(base->gpio, RESET_PORT, RESET_PIN);

}

void
a4988_sleep(Stepper base)
{
    gpio_reset_pin(base->gpio, SLEEP_PORT, SLEEP_PIN);
}

void
a4988_wakeup(Stepper base)
{
    gpio_set_pin(base->gpio, SLEEP_PORT, SLEEP_PIN);
}