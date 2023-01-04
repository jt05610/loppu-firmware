/**
  ******************************************************************************
  * @file   holding_registers.h
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
#ifndef PRESSSURESENSOR_HOLDING_REGISTERS_H
#define PRESSSURESENSOR_HOLDING_REGISTERS_H

#include "modbus.h"

void holding_registers_create(PrimaryTable base, Device device);

#endif //PRESSSURESENSOR_HOLDING_REGISTERS_H