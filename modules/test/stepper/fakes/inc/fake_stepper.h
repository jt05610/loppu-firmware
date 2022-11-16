/**
  ******************************************************************************
  * @file   fake_stepper.h
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

#ifndef DRIVERS_FAKE_STEPPER_H
#define DRIVERS_FAKE_STEPPER_H

#include "stepper/stepper_driver.h"

void fake_stepper_create(Stepper base, gpio_t *gpio);

#endif //DRIVERS_FAKE_STEPPER_H
