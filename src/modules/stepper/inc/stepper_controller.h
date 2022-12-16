/**
  ******************************************************************************
  * @file   stepper_controller.h
  * @author Jonathan Taylor
  * @date   11/15/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_STEPPER_CONTROLLER_H
#define DRIVERS_STEPPER_CONTROLLER_H
#include "stepper_driver.h"
#include "../../../lib/drivers/timer/inc/timer.h"

#define UPDATE_FREQUENCY 1000 //Hz

typedef struct stepper_controller_t * StepperController;

typedef struct stepper_kinematics_t
{
    int32_t position; // steps
    int32_t velocity; // steps / s
    int32_t acceleration; // steps / s^2

} stepper_kinematics_t;

typedef enum stepper_state_t
{
    STEPPER_IDLE,
    STEPPER_MOVING,
    STEPPER_STOPPING,
} stepper_state_t;

void stepper_controller_create(StepperController base, uint32_t update_freq, Timer timer);

void stepper_controller_set_target(StepperController base, stepper_kinematics_t *target);
stepper_kinematics_t * stepper_controller_get_target(StepperController base);

/**
 * call at regular intervals
 * @param base
 */
void stepper_update(StepperController base);

void stepper_controller_enable(StepperController base);
void stepper_controller_disable(StepperController base);

void stepper_controller_set_current(StepperController base, stepper_kinematics_t * current);

#include ".private/stepper_controller_private.h"
#endif // DRIVERS_STEPPER_CONTROLLER_H