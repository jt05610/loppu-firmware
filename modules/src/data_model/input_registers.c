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

static struct input_registers_t
{
    PrimaryTable base;
    ir_handler_t *handlers;
} self = {};

static uint16_t
input_registers_read(PrimaryTable base, uint16_t address)
{
    return self.handlers[address]();
}

static primary_table_interface_t interface = {
        .read = input_registers_read,
        .write = 0
};

void
input_registers_create(PrimaryTable base, ir_handler_t * handlers)
{
    base->vtable = &interface;
    self.base = base;
    self.handlers = handlers;

}


