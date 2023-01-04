/**
  ******************************************************************************
  * @file   holding_registers.h
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
#ifndef FAKEDEVICE_HOLDING_REGISTERS_H
#define FAKEDEVICE_HOLDING_REGISTERS_H

#include "modbus.h"

void holding_registers_create(PrimaryTable base, Device device);

#endif //FAKEDEVICE_HOLDING_REGISTERS_H