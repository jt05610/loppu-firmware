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
    int32_t     next_pos;
    int32_t     next_vel;
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
        stepdir_set_ms(self.stepdir, self.last_ms);
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
    stepdir_rotate(_SD, -STEPDIR_MAX_VELOCITY);
    axis->state = AXIS_HOMING;

}

void
axis_goto(Axis axis, int32_t position, int32_t vel)
{
    axis_plan(axis, position, vel);
    axis_start(axis);
}

void
axis_plan(Axis axis, int32_t position, int32_t vel)
{
    axis->next_pos = position * STEPS_PER_MM * (1 << _SD->ms) / 1000;
    axis->next_vel = (vel * STEPS_PER_MM * (1 << _SD->ms)) / 1000;
}

void
axis_start(Axis axis)
{
    stepdir_set_vel_max(_SD, axis->next_vel);
    stepdir_move_to(_SD, axis->next_pos);
}

void
axis_stop(Axis axis)
{
    stepdir_stop(_SD, STEPDIR_STOP_NOW);
}

bool axis_homed(Axis axis)
{
    return axis->state == AXIS_HOMED;
}

uint8_t axis_state(Axis axis)
{
    return axis->state;
}

void axis_nudge(Axis axis, int32_t amount)
{
    stepdir_move_rel(_SD, amount * STEPS_PER_MM * (1 << _SD->ms) / 1000);
}
