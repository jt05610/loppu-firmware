/**
  ******************************************************************************
  * @file   discrete_inputs.h
  * @author jtaylor
  * @date   12 Dec 2022
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef FAKEDEVICE_DISCRETE_INPUTS_H
#define FAKEDEVICE_DISCRETE_INPUTS_H

#include "modbus.h"

void discrete_inputs_create(PrimaryTable base, void * device);

#endif //FAKEDEVICE_DISCRETE_INPUTS_H