/**
  ******************************************************************************
  * @file   input_registers.h
  * @author Jonathan Taylor
  * @date   11/19/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_INPUT_REGISTERS_H
#define INJECTOR_INPUT_REGISTERS_H
#include <stdint-gcc.h>

#include "data_model/primary_table.h"

typedef uint16_t (*ir_handler_t)();

void input_registers_create(PrimaryTable base, ir_handler_t * handlers);

#endif //INJECTOR_INPUT_REGISTERS_H
