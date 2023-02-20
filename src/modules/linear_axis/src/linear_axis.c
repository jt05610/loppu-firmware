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

#define AXIS_IDLE 0x00
#define AXIS_HOMING 0x01
#define AXIS_HOMED 0x02
#define AXIS_STALLED 0x03

typedef struct axis_t
{
    StepDir stepdir;
    uint8_t state;
    uint8_t home_bounce_count;
    uint32_t max_pos;
} axis_t;

#define _SD (self.stepdir)

static axis_t self = {0};

static inline void on_stalled();

Axis
axis_create(StepDir stepdir)
{
    self.stepdir = stepdir;
    self.state = AXIS_IDLE;
    return &self;
}

void
axis_home(Axis axis)
{
    stepdir_rotate(_SD, -STEPDIR_MAX_VELOCITY);
}

void axis_goto(Axis axis, int32_t position, int32_t vel)
{

}


void
axis_plan(Axis axis, int32_t position, int32_t vel)
{

}

void
axis_start(Axis axis)
{

}

void
axis_pause(Axis axis, uint32_t ms)
{

}

void
axis_stop(Axis axis)
{

}

void
axis_stall_handler()
{

}

bool axis_homed(Axis axis)
{
    return axis->state == AXIS_HOMED;
}
