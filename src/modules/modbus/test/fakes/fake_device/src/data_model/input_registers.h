/**
  ******************************************************************************
  * @file   input_registers.h
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
#ifndef FAKEDEVICE_INPUT_REGISTERS_H
#define FAKEDEVICE_INPUT_REGISTERS_H

#include "modbus.h"

void input_registers_create(PrimaryTable base, void * device);

#endif //FAKEDEVICE_INPUT_REGISTERS_H