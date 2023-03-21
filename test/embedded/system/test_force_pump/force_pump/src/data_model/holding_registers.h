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

void holding_registers_create(PrimaryTable base, Device device);

#endif //FORCE_PUMP_HOLDING_REGISTERS_H