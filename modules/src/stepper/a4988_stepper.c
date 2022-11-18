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

static a4988_init_t * self = {0};

static inline void
set_dir(Stepper base, dir_t dir)
{
    if (Backward == dir)
        gpio_set_pin(base->gpio, self->dir_port, self->dir_pin);
    else
        gpio_reset_pin(base->gpio, self->dir_port, self->dir_pin);
}

static inline void
a4988_set_microstep(Stepper base, microstep_t microstep)
{
    switch (microstep)
    {
        case MS_FULL:
            gpio_reset_pin(base->gpio, MS_PORT, RESET_PINS_FULL);
            break;
        case MS_2:
            gpio_reset_pin(base->gpio, MS_PORT, RESET_PINS_HALF);
            gpio_set_pin(base->gpio, MS_PORT, SET_PINS_HALF);
            break;
        case MS_4:
            gpio_reset_pin(base->gpio, MS_PORT, RESET_PINS_QUARTER);
            gpio_set_pin(base->gpio, MS_PORT, SET_PINS_QUARTER);
            break;
        case MS_8:
            gpio_reset_pin(base->gpio, MS_PORT, RESET_PINS_EIGHTH);
            gpio_set_pin(base->gpio, MS_PORT, SET_PINS_EIGHTH);
            break;
        case MS_16:
            gpio_set_pin(base->gpio, MS_PORT, SET_PINS_SIXTEENTH);
            break;
        default:
            break;
    }
}

static inline void
step(Stepper base)
{
    gpio_toggle(base->gpio, self->step_port, self->step_pin);
}

static inline void
enable(Stepper base)
{
    gpio_reset_pin(base->gpio, self->enable_port, self->enable_pin);
}

static inline void
disable(Stepper base)
{
    gpio_set_pin(base->gpio, self->enable_port, self->enable_pin);
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
    params->base->vtable = &interface;
    params->base->gpio = params->gpio;
    self = params;
}

void a4988_reset(Stepper base)
{
    gpio_reset_pin(base->gpio, self->reset_port, self->reset_pin);

}
void a4988_set(Stepper base)
{
    gpio_set_pin(base->gpio, self->reset_port, self->reset_pin);
}

void
a4988_sleep(Stepper base)
{
    gpio_reset_pin(base->gpio, self->sleep_port, self->sleep_pin);
}

void
a4988_wakeup(Stepper base)
{
    gpio_set_pin(base->gpio, self->sleep_port, self->sleep_pin);
}