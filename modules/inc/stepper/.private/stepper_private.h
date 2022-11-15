/**
  ******************************************************************************
  * @file   stepper_private.h
  * @author Jonathan Taylor
  * @date   7/11/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_STEPPER_PRIVATE_H
#define DRIVERS_STEPPER_PRIVATE_H

#include "sized_array.h"
#include "stepper/stepper.h"
#include "timer/pwm.h"
#include "timer/timer.h"

typedef enum microstep_t
{
    FULL_STEP,
    HALF_STEP,
    QUARTER_STEP,
    EIGHTH_STEP,
    SIXTEENTH_STEP
} microstep_t;

typedef enum dir_t
{
    Forward,
    Backward
} dir_t;

typedef struct stepper_params_t
{
    uint32_t position;     /* steps */
    uint32_t speed;        /* steps / s */
    uint32_t accel;        /* steps / s^2 */
    dir_t    dir;
} stepper_params_t;

typedef struct stepper_interface_t
{
    void (* set_course)(void);

    void (* run)(void);

    bool (* is_idle)(void);

    void (* set_position)(uint32_t pos);
} stepper_interface_t;

typedef struct stepper_t
{
    StepperInterface vtable;
    StepperParams    target;
    Timer            time;
    PWM              pwm;
} stepper_t;

#endif //DRIVERS_STEPPER_PRIVATE_H
