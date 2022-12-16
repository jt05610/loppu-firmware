/**
  ******************************************************************************
  * @file   holding_registers.h
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
#ifndef FAKEDEVICE_HOLDING_REGISTERS_H
#define FAKEDEVICE_HOLDING_REGISTERS_H

#include "modbus.h"

void holding_registers_create(PrimaryTable base, void * device);

#endif //FAKEDEVICE_HOLDING_REGISTERS_H