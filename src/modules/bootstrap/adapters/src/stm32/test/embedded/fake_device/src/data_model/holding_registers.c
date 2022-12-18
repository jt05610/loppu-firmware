/**
  ******************************************************************************
  * @file   holding_registers.c
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
#include "holding_registers.h"

/* end includes code */


/* start macros code */

#define N_HOLDING_REGISTERS 1

/* end macros code */


/* start struct code */

static struct {
    void * device;
} self = {0};

/* end struct code */


static inline void read_hr_1(void * device, sized_array_t * dest);
static inline void write_hr_1(void * device, uint16_t value);

static pt_read_t read_handlers[N_HOLDING_REGISTERS] = {
    read_hr_1,
};

static pt_write_t write_handlers[N_HOLDING_REGISTERS] = {
    write_hr_1,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
holding_registers_create(PrimaryTable base, void * device)
{
    base->vtable = &interface;
    base->device = device;

    /* start create code */


    /* end create code */
}
static inline void
read_hr_1(void * device, sized_array_t * dest)
{
    FakeDevice d = (FakeDevice) device;
    /* start read_hr_1 code */
    dest->size = 2;
    uint16_t value = fake_device_get_value(d, HR_TABLE);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 0, value)
    /* end read_hr_1 code */
}

static inline void
write_hr_1(void * device, uint16_t value)
{
    FakeDevice d = (FakeDevice) device;

    /* start write_hr_1 code */
    fake_device_set_value(d, HR_TABLE, value);
    /* end write_hr_1 code */
}

