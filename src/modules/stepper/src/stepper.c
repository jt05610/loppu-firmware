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

#include "stepper.h"

uint8_t
stepper_get_dir(Stepper base)
{
    if (base && base->vtable && base->vtable->get_dir)
        return base->vtable->get_dir();
    return 0;
}

void
stepper_set_dir(Stepper base, uint8_t dir)
{
    if (base && base->vtable && base->vtable->set_dir)
        base->vtable->set_dir(dir);
}

int32_t
stepper_get_velocity(Stepper base)
{
    if (base && base->vtable && base->vtable->get_velocity)
        return base->vtable->get_velocity();
    return 0;
}

void
stepper_set_velocity(Stepper base, int32_t value)
{
    if (base && base->vtable && base->vtable->set_velocity)
        base->vtable->set_velocity(value);

}

microstep_t
stepper_get_microstep(Stepper base)
{
    if (base && base->vtable && base->vtable->get_microstep)
        return base->vtable->get_microstep();
    return 0;
}

void
stepper_set_microstep(Stepper base, microstep_t microstep)
{
    if (base && base->vtable && base->vtable->set_microstep)
        base->vtable->set_microstep(microstep);
}

bool
stepper_get_enabled(Stepper base)
{
    if (base && base->vtable && base->vtable->get_enabled)
        return base->vtable->get_enabled();
    return 0;
}

void
stepper_set_enabled(Stepper base, bool enabled)
{
    if (base && base->vtable && base->vtable->set_enabled)
        base->vtable->set_enabled(enabled);
}

void
stepper_periodic_job(Stepper base)
{
    if (base && base->vtable && base->vtable->periodic_job)
        base->vtable->periodic_job();
}

int32_t stepper_get_tstep(Stepper base) {
    if (base && base->vtable && base->vtable->get_tstep)
        return base->vtable->get_tstep();
    return 0;
}

int32_t stepper_get_stallguard(Stepper base) {
    if (base && base->vtable && base->vtable->get_stall)
        return base->vtable->get_stall();
    return 0;
}
