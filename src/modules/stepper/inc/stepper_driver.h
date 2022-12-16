/**
  ******************************************************************************
  * @file   stepper.h
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

#ifndef DRIVERS_STEPPER_H
#define DRIVERS_STEPPER_H

#include "../../modbus/inc/public/modbus/project_types.h"
#include "../../../lib/drivers/gpio/inc/gpio.h"

typedef struct stepper_t           * Stepper;
typedef struct stepper_interface_t * StepperInterface;

typedef enum dir_t
{
    Backward,
    Forward,
} dir_t;

typedef enum microstep_t
{
    MS_FULL,
    MS_2,
    MS_4,
    MS_8,
    MS_16,
    MS_32,
    MS_64,
    MS_128,
    MS_256
} microstep_t;

void stepper_set_dir(Stepper base, dir_t dir);

void stepper_step(Stepper base);

void stepper_set_microstep(Stepper base, microstep_t microstep);

void stepper_enable(Stepper base);

void stepper_disable(Stepper base);

#endif //DRIVERS_STEPPER_H

#include ".private/stepper_private.h"