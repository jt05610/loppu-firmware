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

#include "../../../modbus/inc/public/modbus/project_types.h"
#include "../stepper_driver.h"

typedef struct stepper_interface_t
{
    void (* step)(Stepper base);

    void (* set_dir)(Stepper base, dir_t dir);

    void (* set_microstep)(Stepper base, microstep_t microstep);

    void (* enable)(Stepper base);

    void (* disable)(Stepper base);

} stepper_interface_t;

typedef struct stepper_t
{
    StepperInterface vtable;
    GPIO             gpio;
} stepper_t;

#endif //DRIVERS_STEPPER_PRIVATE_H
