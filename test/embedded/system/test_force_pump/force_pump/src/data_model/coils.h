/**
  ******************************************************************************
  * @file   coils.h
  * @author jtaylor
  * @date   21 Mar 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef FORCE_PUMP_COILS_H
#define FORCE_PUMP_COILS_H

#include "modbus.h"
#include "linear_axis.h"

void coils_create(PrimaryTable base, Device device, Axis axis);

#endif //FORCE_PUMP_COILS_H