/**
  ******************************************************************************
  * @file   linear_axis.c
  * @author Jonathan Taylor
  * @date   11/15/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <math.h>
#include "stepper/linear_axis.h"
#include "stm32g0xx_ll_exti.h"

void
linear_axis_create(
        LinearAxis axis, StepperController controller, double steps_per_mm
)
{
    axis->steps_per_mm = steps_per_mm;
    axis->controller   = controller;
    axis->state        = AXIS_DISABLED;
    axis->target       = 0;
    axis->velocity     = 0;
    axis->accel        = 0;
    axis->new_position = false;
    axis->keep_moving  = false;
}

void
linear_axis_home(LinearAxis axis)
{
    stepper_kinematics_t target = {
            -axis->controller->max_pos,
            -axis->controller->max_velocity,
            0
    };
    stepper_controller_set_target(axis->controller, &target);
    axis->state = AXIS_HOMING;
}

typedef void (* axis_state_handler)(LinearAxis axis);

static inline int32_t
mm_to_steps(LinearAxis axis, double position)
{
    return (int32_t) floor(position * axis->steps_per_mm);
}

static inline void
handle_idle(LinearAxis axis)
{
    if (axis->new_position)
    {
        stepper_controller_enable(axis->controller);
        stepper_kinematics_t target = {
                mm_to_steps(axis, axis->target),
                mm_to_steps(axis, axis->velocity),
                axis->accel
        };
        stepper_controller_set_target(axis->controller, &target);
        axis->state        = AXIS_MOVING;
        axis->new_position = false;
    }
}

static inline void
handle_moving(LinearAxis axis)
{
    if (axis->new_position)
    {
        stepper_kinematics_t target = {
                mm_to_steps(axis, axis->target),
                mm_to_steps(axis, axis->velocity),
                axis->accel
        };
        stepper_controller_set_target(axis->controller, &target);
        axis->state        = AXIS_MOVING;
        axis->new_position = false;
    }
    if (axis->controller->state == STEPPER_IDLE)
    {

        axis->state = AXIS_IDLE;
    }
}

static inline void
handle_homing(LinearAxis axis)
{
    /*
     * Do I need to do anything in here?
     */
}

static inline void
handle_home_triggered(LinearAxis axis)
{
    stepper_kinematics_t current = {
            0,
            0,
            0
    };
    stepper_controller_set_target(axis->controller, &current);
    stepper_controller_set_current(axis->controller, &current);
    axis->state = AXIS_IDLE;
}

static inline void
handle_disabled(LinearAxis axis)
{
    stepper_controller_disable(axis->controller);
}

static axis_state_handler handlers[5] = {
        handle_idle,
        handle_moving,
        handle_homing,
        handle_home_triggered,
        handle_disabled
};

void
linear_axis_update(LinearAxis axis)
{
    handlers[axis->state](axis);
    stepper_update(axis->controller);
}

void
linear_axis_enable(LinearAxis axis)
{
    stepper_controller_enable(axis->controller);
    axis->state = AXIS_IDLE;
}

void
linear_axis_disable(LinearAxis axis)
{
    stepper_controller_disable(axis->controller);
    axis->state = AXIS_DISABLED;
}

void
linear_axis_go_to(LinearAxis axis, double position)
{
    axis->target       = position;
    axis->new_position = true;
}

double
linear_axis_current_position(LinearAxis axis)
{
    return (1.0 * (double) axis->controller->ramp.position) /
           (axis->steps_per_mm);
}

double
linear_axis_current_velocity(LinearAxis axis)
{
    return (1.0 * (double) axis->controller->ramp.velocity) /
           (axis->steps_per_mm);
}

void
linear_axis_set_steps_per_mm(LinearAxis axis, double steps_per_mm)
{
    axis->steps_per_mm = steps_per_mm;
}

void
linear_axis_set_accel(LinearAxis axis, double accel)
{
    axis->accel = accel;
}

void
linear_axis_home_interrupt(LinearAxis axis)
{
    axis->state = AXIS_HOME_TRIGGERED;
}

void linear_axis_set_velocity(LinearAxis axis, double velocity)
{
    axis->velocity = velocity;
}
