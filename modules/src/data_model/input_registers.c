/**
  ******************************************************************************
  * @file   input_registers.c
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

#include "data_model/input_registers.h"

void
input_registers_create(InputRegisters base, ir_handler_t * handlers)
{
    base->handlers = handlers;
}

uint16_t input_registers_read(InputRegisters base, uint16_t address)
{
    return base->handlers[address]();
}
