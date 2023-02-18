/**
  ******************************************************************************
  * @file   linear_axis.h
  * @author Jonathan Taylor
  * @date   2/17/23
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

#include <stdint.h>
#include "stepdir.h"

#define STEPS_PER_MM 400

#define MICROSTEP 256

#define MICROSTEPS_PER_MM STEPS_PER_MM * MICROSTEP

typedef struct axis_t * Axis;

Axis axis_create(StepDir stepdir);

void axis_home(Axis axis);

bool axis_homed(Axis axis);

void axis_goto(Axis axis, int32_t position, int32_t vel);

void axis_plan(Axis axis, int32_t position, int32_t vel);

void axis_start(Axis axis);

void axis_pause(Axis axis, uint32_t ms);

void axis_stop(Axis axis);

void axis_stall_handler();

#endif //INJECTOR_LINEAR_AXIS_H
