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

#define AXIS_UNKNOWN 0x00
#define AXIS_IDLE 0x01
#define AXIS_HOMING 0x02
#define AXIS_HOMED 0x03
#define AXIS_STALLED 0x04
#define AXIS_FORWARD_STALL 0x05
#define AXIS_MOVING 0x06
#define AXIS_ERROR 0xFF

typedef struct axis_t *Axis;

typedef struct axis_params_t *AxisParams;

typedef struct axis_params_t {
    uint32_t home_timeout;
    void * timeout_timer;
    int32_t max_pos;
    int32_t max_vel;
    int32_t accel;
    microstep_t ms;
    int32_t steps_per_m;
    StepDir step_dir;
    microstep_t home_ms;
    int32_t home_vel;
} axis_params_t;

Axis axis_create(AxisParams params);

void axis_update(Axis axis);

void axis_home(Axis axis);

void axis_forward_stall(Axis axis);

bool axis_homed(Axis axis);

bool axis_is_moving(Axis axis);

uint8_t axis_state(Axis axis);

void axis_goto(Axis axis, uint16_t position);

uint16_t axis_current_pos(Axis axis);

uint16_t axis_current_vel(Axis axis);

void axis_set_zero(Axis axis);

void axis_set_accel(Axis axis, uint16_t accel);

uint16_t axis_get_accel(Axis axis);

void axis_set_target_pos(Axis axis, uint16_t position);

void axis_set_target_vel(Axis axis, uint16_t vel);

uint16_t axis_get_target_pos(Axis axis);

uint16_t axis_get_target_vel(Axis axis);

void axis_set_steps_per_m(Axis axis, int32_t steps_per_m);

int32_t axis_get_steps_per_m(Axis axis);

void axis_start(Axis axis);

void axis_nudge(Axis axis, int32_t amount);

void axis_stop(Axis axis);

void axis_set_enabled(Axis axis, bool enabled);

bool axis_get_enabled(Axis axis);

#endif //INJECTOR_LINEAR_AXIS_H
