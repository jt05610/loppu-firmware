/**
  ******************************************************************************
  * @file   stepdir.c
  * @author Jonathan Taylor
  * @date   2/16/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "stepdir.h"
#include "gpio.h"
#include "timer.h"
#include "tmc/ramp/LinearRamp1.h"
#include "ic/tmc2209_stepper.h"

static TMC_LinearRamp ramp;

static stepdir_t self = {0};

static inline void stop(StepDir base, uint8_t stop_type);

static inline int32_t
step_diff(int32_t vel, uint32_t old_accel, uint32_t new_accel);

void
stepdir_stop(StepDir base, uint8_t stop_type)
{
    stop(base, stop_type);
}

void
stepdir_rotate(StepDir base, int32_t vel)
{
    tmc_ramp_linear_set_mode(base->ramp, TMC_RAMP_LINEAR_MODE_VELOCITY);
    tmc_ramp_linear_set_targetVelocity(
            self.ramp, MIN(STEPDIR_MAX_VELOCITY, vel));
}


void
stepdir_move_to(StepDir base, int32_t pos)
{
    tmc_ramp_linear_set_mode(base->ramp, TMC_RAMP_LINEAR_MODE_POSITION);
    tmc_ramp_linear_set_targetPosition(base->ramp, pos);
}

void
stepdir_move_rel(StepDir base, int32_t pos)
{
    stepdir_move_to(base, tmc_ramp_linear_get_rampPosition(base->ramp) + pos);
}

uint8_t
stepdir_get_state(StepDir base)
{
    return base->state;
}

void
stepdir_periodic_job()
{
    gpio_reset_pin(
            self.stepper->hal->gpio, self.stepper->port,
            self.stepper->step_pin);
    int32_t dx = tmc_ramp_linear_compute(self.ramp);
    if (dx) {
        stepper_set_dir(self.stepper, dx <= 0);
        gpio_set_pin(
                self.stepper->hal->gpio, self.stepper->port,
                self.stepper->step_pin);
    }
    if (self.new_accel == tmc_ramp_linear_get_acceleration(self.ramp)) {
        tmc_ramp_linear_set_acceleration(self.ramp, self.new_accel);
        self.old_vel = tmc_ramp_linear_get_rampVelocity(self.ramp);
    }
    if (self.accel_steps_updated) {
        ramp.accelerationSteps += self.step_difference;
        self.accel_steps_updated = false;
    }
}

uint8_t
stepdir_get_status(StepDir base)
{
    uint8_t status = base->state;
    status |= (stepdir_get_target_pos(base) == stepdir_get_pos(base)) ?
              STEPDIR_STATUS_TARGET_REACHED : 0;
    status |= (base->stalled) ? STEPDIR_STATUS_STALLED : 0;
    status |= (tmc_ramp_linear_get_mode(self.ramp) ==
               TMC_RAMP_LINEAR_MODE_VELOCITY) ? STEPDIR_STATUS_MODE : 0;
    return status;
}

void
stepdir_limit_pressed()
{
    stop(&self, STEPDIR_STOP_STALL);
}

/* Getters */

int32_t
stepdir_get_pos(StepDir base)
{
    return tmc_ramp_linear_get_rampPosition(base->ramp);
}

int32_t
stepdir_get_target_pos(StepDir base)
{
    return tmc_ramp_linear_get_targetPosition(base->ramp);
}

int32_t
stepdir_get_vel(StepDir base)
{

    return tmc_ramp_linear_get_rampVelocity(base->ramp);
}

int32_t
stepdir_get_target_vel(StepDir base)
{
    return tmc_ramp_linear_get_targetVelocity(base->ramp);
}

int32_t
stepdir_get_vel_max(StepDir base)
{
    return tmc_ramp_linear_get_maxVelocity(base->ramp);
}

uint32_t
stepdir_get_accel(StepDir base)
{
    return tmc_ramp_linear_get_acceleration(base->ramp);
}

uint32_t
stepdir_get_accel_max(StepDir base)
{
    (void) base;
    return STEPDIR_MAX_ACCELERATION;
}

uint32_t
stepdir_get_freq(StepDir base)
{
    return base->freq;
}

uint32_t
stepdir_get_precision(StepDir base)
{
    return tmc_ramp_linear_get_precision(base->ramp);
}

/* Setters */

void
stepdir_set_pos(StepDir base, int32_t pos)
{
    if (tmc_ramp_linear_get_mode(base->ramp) ==
        TMC_RAMP_LINEAR_MODE_POSITION) {
        tmc_ramp_linear_set_targetPosition(base->ramp, pos);
    }
    tmc_ramp_linear_set_rampPosition(base->ramp, pos);
}

void
stepdir_set_accel(StepDir base, uint32_t accel)
{
    if (tmc_ramp_linear_get_mode(base->ramp) ==
        TMC_RAMP_LINEAR_MODE_VELOCITY) {
        tmc_ramp_linear_set_acceleration(base->ramp, accel);
        return;
    }
    if (accel == 0) {
        return;
    }
    uint32_t old_accel = tmc_ramp_linear_get_acceleration(self.ramp);
    tmc_ramp_linear_set_acceleration(base->ramp, accel);
    if (base->state != STEPDIR_STATE_STOPPED) {
        base->new_accel = accel;
    } else {
        tmc_ramp_linear_set_acceleration(base->ramp, accel);
        base->old_vel = tmc_ramp_linear_get_rampVelocity(base->ramp);
    }
    int32_t _step_diff = step_diff(base->old_vel, old_accel, accel);
    if (base->state != STEPDIR_STATE_STOPPED) {
        base->step_difference    = _step_diff;
        self.accel_steps_updated = true;
    } else {
        ramp.accelerationSteps += _step_diff;
    }
}

void
stepdir_set_vel_max(StepDir base, int32_t vel_max)
{
    tmc_ramp_linear_set_maxVelocity(base->ramp, vel_max);
}

void
stepdir_set_freq(StepDir base, uint32_t freq)
{
    base->freq = freq;
    timer_stop(self.stepper->hal->timer, self.stepper->tim_inst);
    timer_start(self.stepper->hal->timer, self.stepper->tim_inst, freq);
}

void
stepdir_set_precision(StepDir base, uint32_t precision)
{
    tmc_ramp_linear_set_precision(base->ramp, precision);
}

static inline int32_t
step_diff(int32_t vel, uint32_t old_accel, uint32_t new_accel)
{
    int64_t tmp = vel;
    tmp = (tmp * 2) + 1;
    tmp = (tmp * tmp) / 4;
    tmp /= 2;
    uint32_t old_steps = tmp / old_accel;
    uint32_t new_steps = tmp / new_accel;
    return new_steps - old_steps;
}

static inline void
stop(StepDir base, uint8_t stop_type)
{
    switch (stop_type) {
        case STEPDIR_STOP_NORMAL:
            tmc_ramp_linear_set_targetVelocity(base->ramp, 0);
            tmc_ramp_linear_set_mode(base->ramp, TMC_RAMP_LINEAR_MODE_VELOCITY);
            break;
        case STEPDIR_STOP_NOW:
        case STEPDIR_STOP_STALL:
        default:
            tmc_ramp_linear_set_rampVelocity(base->ramp, 0);
            ramp.accumulatorVelocity = 0;
            tmc_ramp_linear_set_targetVelocity(base->ramp, 0);
            ramp.accelerationSteps = 0;
            break;
    }
}

StepDir
stepdir_create(
        Stepper stepper,
        uint32_t freq,
        uint32_t precision,
        void (* stall_cb)()
)
{
    self.stepper             = stepper;
    self.freq                = freq;
    self.stalled             = false;
    self.old_vel             = 0;
    self.new_accel           = 0;
    self.step_difference     = 0;
    self.accel_steps_updated = false;
    self.ramp                = &ramp;
    /* Ramp */
    tmc_ramp_linear_init(self.ramp);
    tmc_ramp_linear_set_precision(self.ramp, precision);
    tmc_ramp_linear_set_maxVelocity(self.ramp, STEPDIR_DEFAULT_MAX_VELOCITY);
    tmc_ramp_linear_set_acceleration(
            self.ramp, STEPDIR_DEFAULT_ACCELERATION
    );
    stepper_set_microstep(stepper, MS_FULL);
    /* Limit pin init */
    gpio_attach_cb(
            self.stepper->hal->gpio, self.stepper->port,
            self.stepper->limit_pin, stall_cb, true);
    /* timer init */
    timer_register_update_callback(
            self.stepper->hal->timer, self.stepper->tim_inst,
            stepdir_periodic_job);
    timer_set_timeout(self.stepper->hal->timer, self.stepper->tim_inst, 1);
    timer_start(self.stepper->hal->timer, self.stepper->tim_inst, self.freq);

    return &self;
}

void
stepdir_destroy(StepDir base)
{
}
