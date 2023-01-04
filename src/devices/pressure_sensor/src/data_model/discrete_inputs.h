/**
  ******************************************************************************
  * @file   discrete_inputs.h
  * @author Jonathan Taylor
  * @date   04 Jan 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef PRESSSURESENSOR_DISCRETE_INPUTS_H
#define PRESSSURESENSOR_DISCRETE_INPUTS_H

#include "modbus.h"

void discrete_inputs_create(PrimaryTable base, Device device);

#endif //PRESSSURESENSOR_DISCRETE_INPUTS_H