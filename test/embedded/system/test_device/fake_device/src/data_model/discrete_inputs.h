/**
  ******************************************************************************
  * @file   discrete_inputs.h
  * @author jtaylor
  * @date   03 Jan 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef FAKEDEVICE_DISCRETE_INPUTS_H
#define FAKEDEVICE_DISCRETE_INPUTS_H

#include "modbus.h"

void discrete_inputs_create(PrimaryTable base, Device device);

#endif //FAKEDEVICE_DISCRETE_INPUTS_H