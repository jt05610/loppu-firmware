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

#include "sized_array.h"

typedef struct stepper_t           * Stepper;
typedef struct stepper_interface_t * StepperInterface;
typedef struct stepper_params_t    * StepperParams;

void stepper_set_target(Stepper base, StepperParams params);

StepperParams stepper_get_target(Stepper base);

void stepper_set_course(Stepper base);

void stepper_run(Stepper base);

bool stepper_is_idle(Stepper base);

void stepper_set_position(Stepper base, uint32_t pos);

#endif //DRIVERS_STEPPER_H

#include "stepper/.private/stepper_private.h"
