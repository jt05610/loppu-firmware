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
#include "../stepper_controller.h"

typedef struct stepper_controller_t
{
    volatile Stepper stepper;
    volatile Timer timer;
    volatile uint32_t current_position;
    volatile stepper_kinematics_t ramp;
    volatile stepper_kinematics_t target;
    volatile stepper_kinematics_t accumulator;
    volatile int32_t acceleration_steps;
    volatile stepper_state_t state;
    volatile uint32_t max_pos;
    volatile uint32_t max_velocity;
    volatile uint32_t planned_steps;
    volatile bool updated;
    volatile uint8_t is_forward;
} stepper_controller_t;

#endif //INJECTOR_STEPPER_CONTROLLER_PRIVATE_H
