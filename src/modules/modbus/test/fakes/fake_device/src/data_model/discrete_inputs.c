/**
  ******************************************************************************
  * @file   discrete_inputs.c
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
#include "discrete_inputs.h"

/* end includes code */


/* start macros code */

#define N_DISCRETE_INPUTS 1

/* end macros code */


/* start struct code */

static struct {
    void * device;
} self = {0};

/* end struct code */


static inline void read_c_1(void * device, sized_array_t * dest);

static pt_read_t read_handlers[N_DISCRETE_INPUTS] = {
    read_c_1,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=0,
};

void
discrete_inputs_create(PrimaryTable base, void * device)
{
    base->vtable = &interface;
    base->device = device;

    /* start create code */

    /* end create code */
}
static inline void
read_c_1(void * device, sized_array_t * dest)
{
    FakeDevice d = (FakeDevice) device;
    /* start read_c_1 code */
    dest->size = 1;
    uint16_t value = fake_device_get_value(d, DI_TABLE);
    dest->bytes[0] = value;
    /* end read_c_1 code */
}
