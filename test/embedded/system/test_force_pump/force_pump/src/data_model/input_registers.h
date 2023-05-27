/**
  ******************************************************************************
  * @file   input_registers.h
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
#ifndef NEEDLE_MOVER_INPUT_REGISTERS_H
#define NEEDLE_MOVER_INPUT_REGISTERS_H

#include "modbus.h"
#include "linear_axis.h"
#include "hx711.h"

void input_registers_create(PrimaryTable base, Device device, Axis axis, HX711 sensor);

#endif //NEEDLE_MOVER_INPUT_REGISTERS_H