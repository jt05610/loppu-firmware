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
#include "ic/tmc2209_stepper.h"

#define N_BOUNCES 1
#define REBOUND_FULL_STEPS 200


typedef struct axis_t
{
    StepDir  stepdir;
    uint8_t  state;
    uint8_t  home_bounce_count;
    int32_t max_pos;
} axis_t;

#define _SD (self.stepdir)

#define _STEP (_SD)->stepper

static axis_t self = {0};

static inline void on_stalled();

void on_stalled()
{
    stepdir_stop(_SD, STEPDIR_STOP_NOW);
    if (self.state == AXIS_HOMING) {
        stepdir_set_pos(_SD, 0);
        self.state = AXIS_HOMED;
        stepper_set_microstep(_STEP, MS_16);
    } else {
        self.max_pos = stepdir_get_pos(_SD);
        self.state = AXIS_STALLED;
    }
}

Axis
axis_create(StepDir stepdir)
{
    self.stepdir = stepdir;
    gpio_attach_cb(
            _STEP->hal->gpio, _STEP->port, _STEP->limit_pin,
            on_stalled, true);
    self.state = AXIS_IDLE;
    return &self;
}

void
axis_home(Axis axis)
{
    stepdir_rotate(_SD, -STEPDIR_MAX_VELOCITY);
    axis->state = AXIS_HOMING;

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

uint8_t axis_state(Axis axis)
{
    return axis->state;
}
