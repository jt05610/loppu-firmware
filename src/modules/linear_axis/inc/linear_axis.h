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

#define AXIS_IDLE 0x00
#define AXIS_HOMING 0x01
#define AXIS_HOMED 0x02
#define AXIS_STALLED 0x03

#define STEPS_PER_REV 200
#define REV_PER_MM 1

#define STEPS_PER_MM (STEPS_PER_REV * REV_PER_MM)

typedef struct axis_t * Axis;

Axis axis_create(StepDir stepdir);

void axis_home(Axis axis);

bool axis_homed(Axis axis);

uint8_t axis_state(Axis axis);

void axis_goto(Axis axis, int32_t position, int32_t vel);

void axis_plan(Axis axis, int32_t position, int32_t vel);

void axis_start(Axis axis);

void axis_nudge(Axis axis, int32_t amount);

void axis_stop(Axis axis);

#endif //INJECTOR_LINEAR_AXIS_H
