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
#include "../../../../../lib/drivers/gpio/inc/gpio.h"


static struct fake_stepper
{
    Stepper          base;
    bool enabled;
    bool is_forward;
    int32_t position;
    microstep_t microstep;
} self = {0};

static inline void
step(Stepper base)
{
    self.position += (self.is_forward) ? 1 : -1;
    gpio_toggle(base->gpio, 0, 0);
}

static void
set_dir(Stepper base, dir_t dir)
{
    self.is_forward = dir == Forward;
    if (self.is_forward)
        gpio_set_pin(base->gpio, 0, 0);
    else
        gpio_reset_pin(base->gpio, 0, 0);
}

static inline void
set_microstep(Stepper base, microstep_t microstep)
{
    self.microstep = microstep;
}

static inline void
enable(Stepper base)
{
    self.enabled = true;
}

static inline void
disable(Stepper base)
{
    self.enabled = false;
}

static stepper_interface_t fake_stepper_interface = {
        .step = step,
        .set_dir = set_dir,
        .set_microstep = set_microstep,
        .enable = enable,
        .disable = disable,

};

void
fake_stepper_create(Stepper base, gpio_t * gpio)
{
    base->vtable = &fake_stepper_interface;
    base->gpio = gpio;
    self.base = base;
    self.enabled = false;
    self.position = 0;
    self.microstep = MS_FULL;
    self.is_forward = true;
}
