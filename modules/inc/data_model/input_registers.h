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

typedef struct input_registers_t * InputRegisters;

typedef uint16_t (*ir_handler_t)();

typedef struct input_registers_t
{
    ir_handler_t *handlers;
} input_registers_t;

void input_registers_create(InputRegisters base, ir_handler_t * handlers);
uint16_t input_registers_read(InputRegisters base, uint16_t address);
#endif //INJECTOR_INPUT_REGISTERS_H
