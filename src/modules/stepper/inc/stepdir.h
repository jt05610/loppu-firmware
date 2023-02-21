/**
  ******************************************************************************
  * @file   stepdir.h
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

#ifndef INJECTOR_STEPDIR_H
#define INJECTOR_STEPDIR_H

#include "peripherals.h"
#include "stepper.h"

typedef struct stepdir_t * StepDir;

#define STEPDIR_FREQ (1<<17)
#define STEPDIR_MAX_VELOCITY STEPDIR_FREQ
#define STEPDIR_MAX_ACCELERATION 0xFFFE0000

#define STEPDIR_DEFAULT_ACCELERATION STEPDIR_MAX_ACCELERATION
#define STEPDIR_DEFAULT_MAX_VELOCITY STEPDIR_MAX_VELOCITY
#define STEPDIR_DEFAULT_PRECISION
#define STEPDIR_STOP_NORMAL 0x00
#define STEPDIR_STOP_STALL  0x01
#define STEPDIR_STOP_NOW    0x02

#define STEPDIR_STATE_STOPPED 0x00
#define STEPDIR_STATE_MOVING  0x01
#define STEPDIR_STATE_STOPPING 0x02

#define STEPDIR_STATUS_TARGET_REACHED 0x01 < 0x01
#define STEPDIR_STATUS_STALLED  0x01 < 0x02
#define STEPDIR_STATUS_MODE 0xFF < 0x04


typedef struct stepdir_t
{
    Stepper           stepper;
    uint8_t           state;
    volatile int32_t  old_vel;
    volatile uint32_t new_accel;
    volatile int32_t  step_difference;
    volatile bool     accel_steps_updated;
    volatile bool     stalled;
    uint32_t          freq;
    void * ramp;
} stepdir_t;

StepDir stepdir_create(
        Stepper stepper, uint32_t freq, uint32_t precision,
        void (* stall_cb)());

void stepdir_destroy(StepDir base);

void stepdir_rotate(StepDir base, int32_t vel);

void stepdir_stop(StepDir base, uint8_t stop_type);

void stepdir_move_to(StepDir base, int32_t pos);

void stepdir_move_rel(StepDir base, int32_t pos);

uint8_t stepdir_get_state(StepDir base);

void stepdir_periodic_job();

void stepdir_limit_pressed();

/* Getters */

uint8_t stepdir_get_status(StepDir base);

int32_t stepdir_get_pos(StepDir base);

int32_t stepdir_get_target_pos(StepDir base);

int32_t stepdir_get_vel(StepDir base);

int32_t stepdir_get_target_vel(StepDir base);

int32_t stepdir_get_vel_max(StepDir base);

uint32_t stepdir_get_accel(StepDir base);

uint32_t stepdir_get_accel_max(StepDir base);

uint32_t stepdir_get_freq(StepDir base);

uint32_t stepdir_get_precision(StepDir base);

/* Setters */

void stepdir_set_pos(StepDir base, int32_t pos);

void stepdir_set_accel(StepDir base, uint32_t accel);

void stepdir_set_vel_max(StepDir base, int32_t vel_max);

void stepdir_set_freq(StepDir base, uint32_t freq);

void stepdir_set_precision(StepDir base, uint32_t precision);


#endif //INJECTOR_STEPDIR_H
