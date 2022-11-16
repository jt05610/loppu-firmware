/**
  ******************************************************************************
  * @file   stepper_controller_private.h
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

#ifndef INJECTOR_STEPPER_CONTROLLER_PRIVATE_H
#define INJECTOR_STEPPER_CONTROLLER_PRIVATE_H
#include "stepper/stepper_controller.h"

typedef struct stepper_controller_t
{
    Stepper stepper;
    uint32_t current_position;
    stepper_kinematics_t ramp;
    stepper_kinematics_t target;
    stepper_kinematics_t accumulator;
    int32_t acceleration_steps;
    stepper_state_t state;
    uint32_t max_pos;
    uint32_t max_velocity;
    volatile bool updated;

} stepper_controller_t;

#endif //INJECTOR_STEPPER_CONTROLLER_PRIVATE_H
