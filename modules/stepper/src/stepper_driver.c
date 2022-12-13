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

#include "../inc/stepper_driver.h"

void
stepper_set_dir(Stepper base, dir_t dir)
{

    if (base && base->vtable && base->vtable->set_dir)
        base->vtable->set_dir(base, dir);
}

void
stepper_set_microstep(Stepper base, microstep_t microstep)
{

    if (base && base->vtable && base->vtable->set_microstep)
        base->vtable->set_microstep(base, microstep);
}

void
stepper_step(Stepper base)
{
    if (base && base->vtable && base->vtable->step)
        base->vtable->step(base);
}

void stepper_enable(Stepper base)
{
    if (base && base->vtable && base->vtable->enable)
        base->vtable->enable(base);
}

void stepper_disable(Stepper base)
{
    if (base && base->vtable && base->vtable->disable)
        base->vtable->disable(base);
}