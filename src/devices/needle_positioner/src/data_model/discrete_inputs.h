/**
  ******************************************************************************
  * @file   discrete_inputs.h
  * @author Jonathan Taylor
  * @date   11 Dec 2022
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef NEEDLEPOSITIONER_DISCRETE_INPUTS_H
#define NEEDLEPOSITIONER_DISCRETE_INPUTS_H

#include "../../../../modules/modbus/inc/modbus.h"

void discrete_inputs_create(PrimaryTable base, void * device);

#endif //NEEDLEPOSITIONER_DISCRETE_INPUTS_H