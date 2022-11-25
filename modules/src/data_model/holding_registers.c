/**
  ******************************************************************************
  * @file   holding_regsiters.c
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

#include "data_model/holding_registers.h"

static struct holding_registers_t {
    PrimaryTable base;
    hr_handler_t * handlers;
} self = {0};

static uint16_t
read(PrimaryTable base, uint16_t address)
{
    return self.handlers[address](READ, 0xFF);
}
static void
write(PrimaryTable base, uint16_t address, uint16_t value)
{
    self.handlers[address](WRITE, value);
}

static primary_table_interface_t interface = {
        .read = read,
        .write = write
};

void
holding_registers_create(PrimaryTable table, hr_handler_t * handlers)
{
    table->vtable = &interface;
    self.base = table;
    self.handlers = handlers;
}