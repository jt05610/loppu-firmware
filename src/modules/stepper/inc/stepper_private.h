/**
  ******************************************************************************
  * @file   stepper_private.h
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

#ifndef DRIVERS_STEPPER_PRIVATE_H
#define DRIVERS_STEPPER_PRIVATE_H

#include "stepper.h"
#include "peripherals.h"

typedef struct stepper_interface_t
{
    uint8_t (* get_dir)();

    void (* set_dir)(uint8_t dir);

    int32_t (* get_velocity)();

    void (* set_velocity)(int32_t value);

    microstep_t (* get_microstep)();

    void (* set_microstep)(microstep_t microstep);

    void (* set_enabled)(bool enabled);

    bool (* get_enabled)();

    void (* periodic_job)();

} stepper_interface_t;

typedef struct stepper_t
{
    stepper_interface_t * vtable;
    void                * tim_inst;
    Peripherals hal;
    gpio_pin_t  en_pin;
    gpio_pin_t  step_pin;
    gpio_pin_t  dir_pin;
    gpio_pin_t  limit_pin;
    gpio_port_t port;
} stepper_t;

#endif //DRIVERS_STEPPER_PRIVATE_H
