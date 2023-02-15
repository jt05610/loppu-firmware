/**
  ******************************************************************************
  * @file   input_registers.h
  * @author Jonathan Taylor
  * @date   14 Feb 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef TMC2209EVAL_INPUT_REGISTERS_H
#define TMC2209EVAL_INPUT_REGISTERS_H

#include "modbus.h"

void input_registers_create(PrimaryTable base, Device device);

#endif //TMC2209EVAL_INPUT_REGISTERS_H