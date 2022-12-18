/**
  ******************************************************************************
  * @file   input_registers.c
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

/* start includes code */

#include "fake_device.h"
#include "input_registers.h"

/* end includes code */

/* start macros code */

#define N_INPUT_REGISTERS 1

/* end macros code */

/* start struct code */

static struct {
    void * device;
} self = {0};

/* end struct code */


static inline void read_ir_1(void * device, sized_array_t * dest);

static pt_read_t read_handlers[N_INPUT_REGISTERS] = {
    read_ir_1,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=0,
};

void
input_registers_create(PrimaryTable base, void * device)
{
    base->vtable = &interface;
    base->device = device;

    /* start create code */

    /* end create code */
}

static inline void
read_ir_1(void * device, sized_array_t * dest)
{
    FakeDevice d = (FakeDevice) device;
    /* start read_ir_1 code */
    dest->size = 2;
    uint16_t value = fake_device_get_value(d, IR_TABLE);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 0, value)
    /* end read_ir_1 code */
}
