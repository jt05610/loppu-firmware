/**
  ******************************************************************************
  * @file   linear_axis.h
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

#ifndef INJECTOR_LINEAR_AXIS_H
#define INJECTOR_LINEAR_AXIS_H

#include "stepper_controller.h"
#include "stepper_driver.h"

typedef struct linear_axis_t * LinearAxis;

typedef enum linear_axis_state_t {
    AXIS_IDLE,
    AXIS_MOVING,
    AXIS_HOMING,
    AXIS_HOME_TRIGGERED,
    AXIS_DISABLED,
} linear_axis_state_t;

typedef struct linear_axis_t {
    double steps_per_mm;
    StepperController controller;
    volatile linear_axis_state_t state;
    double target;       // mm
    double velocity;     // mm / s
    double accel;        // mm / s^2
    bool new_position;
} linear_axis_t;

void linear_axis_home_interrupt(LinearAxis axis);
void linear_axis_update(LinearAxis axis);
void linear_axis_create(LinearAxis axis, StepperController controller, double steps_per_mm);
void linear_axis_go_to(LinearAxis axis, double position);
void linear_axis_enable(LinearAxis axis);
void linear_axis_disable(LinearAxis axis);
void linear_axis_home(LinearAxis axis);
void linear_axis_set_steps_per_mm(LinearAxis axis, double steps_per_mm);
void linear_axis_set_accel(LinearAxis axis, double accel);
double linear_axis_current_position(LinearAxis axis);
#endif //INJECTOR_LINEAR_AXIS_H
