/**
  ******************************************************************************
  * @file   tmc2209_stepper.cpp
  * @author Jonathan Taylor
  * @date   11/17/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stepper/tmc2209_stepper.h"
#include "TMC2209.h"

static inline void
set_dir(Stepper base, dir_t dir)
{
}

static inline void
set_microstep(Stepper base, microstep_t microstep)
{

}

static inline void
step(Stepper base)
{
}

static inline void
enable(Stepper base)
{
}

static inline void
disable(Stepper base)
{
}

static stepper_interface_t interface = {
        .step = step,
        .set_dir = set_dir,
        .set_microstep = set_microstep,
        .enable = enable,
        .disable = disable
};

void
tmc2209_stepper_create(tmc2209_init_t * params)
{
    params->base->vtable = &interface;
    tmc2209_init(params->tmc2209, params->channel, params->slaveAddress, params->tmc2209_config, params->registerResetState);
}
