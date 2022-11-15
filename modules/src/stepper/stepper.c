/**
  ******************************************************************************
  * @file   stepper.c
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

#include "stepper/stepper.h"

void
stepper_set_target(Stepper base, StepperParams params)
{
    base->target = params;
}

StepperParams
stepper_get_target(Stepper base)
{
    return base->target;
}

void
stepper_set_course(Stepper base)
{
    if (base && base->vtable && base->vtable->set_course)
        base->vtable->set_course();
}

void
stepper_run(Stepper base)
{
    if (base && base->vtable && base->vtable->run)
        base->vtable->run();
}

bool
stepper_is_idle(Stepper base)
{
    bool ret = true;
    if (base && base->vtable && base->vtable->is_idle)
        ret = base->vtable->is_idle();
    return ret;
}

void
stepper_set_position(Stepper base, uint32_t pos)
{
    if (base && base->vtable && base->vtable->set_position)
        base->vtable->set_position(pos);
}