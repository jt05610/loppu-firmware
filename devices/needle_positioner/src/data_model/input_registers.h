/**
  ******************************************************************************
  * @file   input_registers.h
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
#ifndef NEEDLEPOSITIONER_INPUT_REGISTERS_H
#define NEEDLEPOSITIONER_INPUT_REGISTERS_H

#include "modbus.h"

void input_registers_create(PrimaryTable base, void * device);

#endif //NEEDLEPOSITIONER_INPUT_REGISTERS_H