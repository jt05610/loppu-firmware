/**
  ******************************************************************************
  * @file   holding_registers.h
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
#ifndef FORCE_PUMP_HOLDING_REGISTERS_H
#define FORCE_PUMP_HOLDING_REGISTERS_H

#include "modbus.h"
#include "linear_axis.h"
#include "stepdir.h"

void holding_registers_create(PrimaryTable base, Device device, Axis axis, StepDir stepdir);

#endif //FORCE_PUMP_HOLDING_REGISTERS_H