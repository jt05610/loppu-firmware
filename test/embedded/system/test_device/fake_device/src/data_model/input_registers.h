/**
  ******************************************************************************
  * @file   input_registers.h
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
#ifndef FAKEDEVICE_INPUT_REGISTERS_H
#define FAKEDEVICE_INPUT_REGISTERS_H

#include "modbus.h"

void input_registers_create(PrimaryTable base, Device device);

#endif //FAKEDEVICE_INPUT_REGISTERS_H