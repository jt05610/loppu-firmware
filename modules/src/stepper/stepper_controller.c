/**
  ******************************************************************************
  * @file   stepper_controller.c
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

#include <stdlib.h>
#include "stepper/stepper_controller.h"

#define MAX_POSITION 20000  // steps
#define MAX_VELOCITY 500    // steps / s
#define STOP_VELOCITY 5     // steps / ms
#define HOMING_DISTANCE 5   // steps

#ifndef MIN
#define MIN(a, b) (((a)<(b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a)>(b)) ? (a) : (b))
#endif

void
stepper_controller_create(StepperController base, uint32_t update_freq)
{
    base->target.position     = 0;
    base->target.velocity     = 0;
    base->target.acceleration = 0;
    base->acceleration_steps  = 0;
    base->updated = false;
    base->state               = STEPPER_IDLE;
}

static inline bool
target_is_okay(stepper_kinematics_t * target)
{
    bool result = false;
    if (abs(target->velocity) <= MAX_VELOCITY && target->position >= 0 &&
        target->position <= MAX_POSITION)
    {
        result = true;
    }
    return result;
}

void
stepper_controller_set_target(
        StepperController base, stepper_kinematics_t * target)
{
    if (target_is_okay(target))
    {
        base->target.position     = target->position;
        base->target.velocity     = target->velocity;
        base->target.acceleration = target->acceleration;
    }
}

stepper_kinematics_t *
stepper_controller_get_target(StepperController base)
{
    return &base->target;
}

static inline void
idle_handler(StepperController base)
{
    if (base->ramp.velocity == 0)
    {
        base->acceleration_steps = 0;
    }

    if (base->ramp.position != base->target.position)
    {
        base->state = STEPPER_MOVING;
    }
}

static inline int32_t
delta_position(StepperController base)
{
    int32_t diff = base->target.position - base->ramp.position;
    if (base->ramp.velocity < 0)
    {
        diff *= -1;
    } else if (base->ramp.velocity == 0)
    {
        diff = abs(diff);
    }
    return diff;
}

typedef void (* state_handler)(StepperController base);

static inline void
moving_handler(StepperController base)
{
    uint8_t bias = (base->target.acceleration != 0);
    if (base->acceleration_steps + bias >= delta_position(base))
    {
        base->target.velocity = 0;
        base->state           = STEPPER_STOPPING;
    } else
    {
        base->target.velocity = (base->target.position > base->ramp.position) ?
                                MAX_VELOCITY : -MAX_VELOCITY;
    }
}

static inline void
stopping_handler(StepperController base)
{
    int32_t diff = delta_position(base);
    if (diff)
    {
        if (base->ramp.velocity != 0)
        {
            if (base->acceleration_steps + 1 < diff)
            {
                base->state = STEPPER_MOVING;
            }
        } else
        {
            if (diff <= HOMING_DISTANCE)
            {
                base->target.velocity = (base->target.position >
                                         base->ramp.position) ?
                                        STOP_VELOCITY : -STOP_VELOCITY;
            } else
            {
                base->state = STEPPER_IDLE;
            }
        }

    } else
    {
        if (abs(base->ramp.velocity) <= STOP_VELOCITY)
        {
            base->ramp.velocity   = 0;
            base->target.velocity = 0;
            base->state           = STEPPER_IDLE;
        }
    }
}

state_handler position_handlers[3] = {
        idle_handler,
        moving_handler,
        stopping_handler
};

static inline void
stepper_update_position(StepperController base)
{
    position_handlers[base->state](base);
}

static inline int32_t
stepper_update_velocity(StepperController base)
{
    bool accelerating = base->ramp.velocity != base->target.velocity;
    if (base->target.acceleration == 0)
    {
        base->ramp.velocity        = base->target.velocity;
        base->accumulator.velocity = 0;
    } else
    {
        base->accumulator.velocity += base->target.acceleration;
        int32_t dv = base->accumulator.velocity / UPDATE_FREQUENCY;
        base->accumulator.velocity %= UPDATE_FREQUENCY;

        if (base->ramp.velocity < base->target.velocity)
        {
            base->ramp.velocity = MIN(
                    base->ramp.velocity + dv, base->target.velocity);
        } else if (base->ramp.velocity > base->target.velocity)
        {
            base->ramp.velocity = MAX(
                    base->ramp.velocity - dv, base->target.velocity);
        }
    }
    base->accumulator.position += base->ramp.velocity;
    int32_t dx = base->accumulator.position / (int32_t) UPDATE_FREQUENCY;
    base->accumulator.position %= (int32_t) UPDATE_FREQUENCY;
    if (dx != 0)
    {
        base->ramp.position += (dx > 0) ? 1 : -1;

        base->acceleration_steps += (abs(base->ramp.velocity) <
                                     abs(base->target.velocity)) ?
                                    accelerating : -accelerating;
    }
    return dx;
}

void
stepper_update(StepperController base)
{
    if (base->updated) {
        stepper_update_position(base);
        int32_t dx      = stepper_update_velocity(base);
        bool    forward = dx > 0;
        if (base->current_position != base->ramp.position)
        {
            stepper_set_dir(base->stepper, forward);
            stepper_step(base->stepper);
            base->current_position += forward ? 1 : -1;
        }
        base->updated = false;
    }

}

void stepper_controller_enable(StepperController base)
{

}

void stepper_controller_disable(StepperController base)
{

}

void
stepper_controller_set_current(
        StepperController base, stepper_kinematics_t * current
)
{
    base->ramp.position = current->position;
    base->ramp.velocity = current->velocity;
}
