/**
  ******************************************************************************
  * @file   coils.c
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
#include "coils.h"

/* end includes code */


/* start macros code */

#define N_COILS 1

/* end macros code */


/* start struct code */

static struct {
    void * device;
} self = {0};

/* end struct code */


static inline void read_c_1(void * device, sized_array_t * dest);
static inline void write_c_1(void * device, uint16_t value);

static pt_read_t read_handlers[N_COILS] = {
    read_c_1,
};

static pt_write_t write_handlers[N_COILS] = {
    write_c_1,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
coils_create(PrimaryTable base, void * device)
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
    uint16_t value = fake_device_get_value(d, COIL_TABLE);
    dest->bytes[0] = value;
    /* end read_c_1 code */
}

static inline void
write_c_1(void * device, uint16_t value)
{
    FakeDevice d = (FakeDevice) device;

    /* start write_c_1 code */
    fake_device_set_value(d, COIL_TABLE, value>>15);
    /* end write_c_1 code */
}
