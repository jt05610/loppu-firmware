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

#include <stdlib.h>

#define TOLERANCE 100


typedef struct axis_t {
    uint32_t home_timeout;
    void *timeout_timer;
    StepDir stepdir;
    volatile uint8_t state;
    microstep_t last_ms;
    int32_t steps_per_m;
    int32_t target_pos;
    int32_t target_vel;
    int32_t home_vel;
    int32_t max_pos;
    microstep_t home_ms;
    volatile uint8_t needs_ms_change;
    volatile bool needs_stop;
} axis_t;

#define _SD (axis->stepdir)

static axis_t self = {0};

static void handle_stall() {
    self.needs_stop = true;
    stepdir_stop(self.stepdir, STEPDIR_STOP_NOW);
    axis_set_target_pos(&self, 0xFEEDBEEF);
    self.state = AXIS_STALLED;
    if (self.state == AXIS_HOMING) {
        stepdir_set_pos(self.stepdir, 0);
        self.state = AXIS_HOMED;
        self.needs_ms_change = true;
    } else if (self.state == AXIS_FORWARD_STALL) {
        self.state = AXIS_IDLE;
        self.max_pos = stepdir_get_pos(self.stepdir);
        self.needs_ms_change = true;
    } else {
        self.state = AXIS_STALLED;
    }
    self.needs_stop = false;
    timer_reset(self.stepdir->stepper->hal->timer, self.timeout_timer);
}

Axis
axis_create(const AxisParams params) {
    self.stepdir = params->step_dir;
    stepdir_set_ms(self.stepdir, params->ms);
    self.last_ms = params->ms;
    stepdir_attach_limit_cb(self.stepdir, handle_stall);
    self.state = AXIS_IDLE;
    self.steps_per_m = params->steps_per_m;
    self.home_ms = params->home_ms;
    self.home_vel = params->home_vel;
    self.max_pos = params->max_pos;
    self.timeout_timer = params->timeout_timer;
    self.home_timeout = params->home_timeout;
    return &self;
}


void
axis_home(const Axis axis) {
    axis->last_ms = axis->stepdir->ms;
    stepdir_set_ms(_SD, axis->home_ms);
    stepdir_set_target_vel(_SD, -axis->home_vel);
    //stepdir_move_to(_SD, (-axis->max_pos / 500) * ((1 << _SD->ms) * axis->steps_per_m / 1000));
    stepdir_start(axis->stepdir);
    axis->state = AXIS_HOMING;
    //timer_set_interval_ms(axis->stepdir->stepper->hal->timer, axis->timeout_timer, home_timeout, axis->home_timeout);
}

void
axis_forward_stall(const Axis axis) {
    //timer_set_interval_ms(axis->stepdir->stepper->hal->timer, axis->timeout_timer, home_timeout, axis->home_timeout);
    axis->last_ms = axis->stepdir->ms;
    stepdir_set_ms(_SD, axis->home_ms);
    stepdir_set_target_vel(_SD, axis->home_vel);
    stepdir_start(axis->stepdir);
    axis->state = AXIS_FORWARD_STALL;
}

void
axis_goto(const Axis axis, const int32_t pos) {
    axis_set_target_pos(axis, pos);
}

bool
axis_is_moving(const Axis axis) {
    return stepdir_get_vel(axis->stepdir) != 0;
}

void
axis_set_target_pos(const Axis axis, const int32_t position) {
    axis->target_pos = position;
}

int32_t axis_current_pos(const Axis axis) {
    const int32_t current = stepdir_get_pos(axis->stepdir);
    if (current <= 0) {
        return 0;
    }
    return current;
}

int32_t axis_max_pos(const Axis axis) {
    return self.max_pos;
}

int32_t axis_current_vel(const Axis axis) {
    // v is in 1/256 steps per second
    const int32_t v = stepdir_get_vel(axis->stepdir);
    if (v == 0) {
        return 0;
    }
    return v;
}

void
axis_set_target_vel(const Axis axis, const int32_t vel) {
    axis->target_vel = vel;
}

int32_t
axis_get_target_pos(const Axis axis) {
    return axis->target_pos;
}

int32_t
axis_get_target_vel(const Axis axis) {
    return axis->target_vel;
}

void
axis_start(const Axis axis) {
    int32_t vel = abs(axis->target_vel);
    stepdir_set_target_vel(_SD, vel);
    stepdir_move_to(_SD, axis->target_pos);
    stepdir_start(_SD);
    axis->state = AXIS_MOVING;
}

void axis_await_stopped(Axis axis) {
    while (axis_state(axis) == AXIS_MOVING) {
        axis_update(axis);
    }
    axis_update(axis);
}

void
axis_stop(const Axis axis) {
    stepdir_stop(_SD, STEPDIR_STOP_NOW);
}

bool
axis_homed(const Axis axis) {
    return axis->state == AXIS_HOMED;
}

uint8_t
axis_state(const Axis axis) {
    return axis->state;
}

void
axis_set_steps_per_m(const Axis axis, const int32_t steps_per_m) {
    axis->steps_per_m = steps_per_m;
}

int32_t
axis_get_steps_per_m(const Axis axis) {
    return axis->steps_per_m;
}

void
axis_nudge(const Axis axis, const int32_t amount) {
    stepdir_move_rel(_SD, amount * axis->steps_per_m * (1 << _SD->ms) / 1000);
}

void
axis_set_zero(const Axis axis) {
    stepdir_set_pos(axis->stepdir, 0);
}

void
axis_set_enabled(const Axis axis, const bool enabled) {
    stepper_set_enabled(axis->stepdir->stepper, enabled);
}

bool
axis_get_enabled(const Axis axis) {
    return stepper_get_enabled(axis->stepdir->stepper);
}

void
axis_set_accel(const Axis axis, const int32_t accel) {
    stepdir_set_accel(axis->stepdir, ((int32_t) accel * 200 * 256) / 1000);
}

uint16_t
axis_get_accel(const Axis axis) {
    return ((uint16_t) stepdir_get_accel(axis->stepdir) * 1000) / (200 * 256);
}

uint8_t update_state(Axis axis) {
    if (axis->needs_stop) {
        axis->needs_stop = false;
        return AXIS_IDLE;
    }
    if (axis->state == AXIS_HOMING || axis->state == AXIS_FORWARD_STALL) {
        return axis->state;
    }
    if (!stepdir_is_moving(axis->stepdir)) {
        return AXIS_IDLE;
    }
    return axis->state;
}

void axis_update(const Axis axis) {
    stepdir_update(axis->stepdir);
    axis->state = update_state(axis);
}
