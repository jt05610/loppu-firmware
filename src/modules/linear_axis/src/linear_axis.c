/**
  ******************************************************************************
  * @file   linear_axis.c
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

#include "linear_axis.h"


typedef struct axis_t
{
    StepDir     stepdir;
    uint8_t     state;
    microstep_t last_ms;
    uint16_t    target_pos;
    uint16_t    target_vel;
} axis_t;

#define _SD (axis->stepdir)

static axis_t self = {0};

static inline void on_stalled();

void on_stalled()
{
    stepdir_stop(self.stepdir, STEPDIR_STOP_NOW);
    if (self.state == AXIS_HOMING) {
        stepdir_set_pos(self.stepdir, 0);
        self.state = AXIS_HOMED;
    } else if (self.state == AXIS_FORWARD_STALL) {
        self.state = AXIS_IDLE;
    } else {
        self.state = AXIS_STALLED;
    }

}

Axis
axis_create(StepDir stepdir)
{
    self.stepdir = stepdir;
    stepdir_set_ms(self.stepdir, MS_16);
    stepdir_attach_limit_cb(self.stepdir, on_stalled);
    self.state = AXIS_IDLE;
    return &self;
}

void
axis_home(Axis axis)
{
    stepdir_set_ms(_SD, MS_FULL);
    stepdir_set_target_vel(_SD, -(STEPDIR_MAX_VELOCITY));
    stepdir_start(axis->stepdir);
    axis->state = AXIS_HOMING;
}

void
axis_forward_stall(Axis axis)
{
    stepdir_set_ms(_SD, MS_FULL);
    stepdir_set_target_vel(_SD, STEPDIR_MAX_VELOCITY);
    stepdir_start(axis->stepdir);
    axis->state = AXIS_FORWARD_STALL;
}

void
axis_goto(Axis axis, uint16_t pos)
{
    axis_set_target_pos(axis, pos);
    axis_start(axis);
}

bool
axis_is_moving(Axis axis)
{
    return stepdir_get_vel(axis->stepdir) != 0;
}

void
axis_set_target_pos(Axis axis, uint16_t position)
{
    axis->target_pos = position;
}

uint16_t axis_current_pos(Axis axis)
{

    return 1000 * stepdir_get_pos(axis->stepdir) /
           (STEPS_PER_MM * 256);
}

uint16_t axis_current_vel(Axis axis)
{
    return stepdir_get_vel(axis->stepdir);
}

void
axis_set_target_vel(Axis axis, uint16_t vel)
{
    axis->target_vel = vel;
}

uint16_t
axis_get_target_pos(Axis axis)
{
    return axis->target_pos;
}

uint16_t
axis_get_target_vel(Axis axis)
{
    return axis->target_vel;
}

void
axis_start(Axis axis)
{
    stepdir_set_ms(_SD, MS_16);
    stepdir_set_target_vel(_SD, axis->target_vel * STEPS_PER_MM * 256 / 1000);
    stepdir_move_to(_SD, axis->target_pos * STEPS_PER_MM * 256 / 1000);
    stepdir_start(_SD);
}

void
axis_stop(Axis axis)
{
    stepdir_stop(_SD, STEPDIR_STOP_NOW);
}

bool
axis_homed(Axis axis)
{
    return axis->state == AXIS_HOMED;
}

uint8_t
axis_state(Axis axis)
{
    return axis->state;
}

void
axis_nudge(Axis axis, int32_t amount)
{
    stepdir_move_rel(_SD, amount * STEPS_PER_MM * (1 << _SD->ms) / 1000);
}

void
axis_set_zero(Axis axis)
{
    stepdir_set_pos(axis->stepdir, 0);
}

void
axis_set_enabled(Axis axis, bool enabled)
{
    stepper_set_enabled(axis->stepdir->stepper, enabled);
}

bool
axis_get_enabled(Axis axis)
{
    return stepper_get_enabled(axis->stepdir->stepper);
}

void
axis_set_accel(Axis axis, uint16_t accel)
{
    stepdir_set_accel(axis->stepdir, ((int32_t) accel * 200 * 256) / 1000);
}

uint16_t
axis_get_accel(Axis axis)
{
    return ((uint16_t) stepdir_get_accel(axis->stepdir) * 1000) / (200 * 256);
}