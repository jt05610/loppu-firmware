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
#ifndef NEEDLE_MOVER_HOLDING_REGISTERS_H
#define NEEDLE_MOVER_HOLDING_REGISTERS_H

#include "modbus.h"
#include "linear_axis.h"

void holding_registers_create(PrimaryTable base, Device device, StepDir stepdir, Axis axis);

#endif //NEEDLE_MOVER_HOLDING_REGISTERS_H