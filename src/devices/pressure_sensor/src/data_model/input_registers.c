/**
  ******************************************************************************
  * @file   input_registers.c
  * @author Jonathan Taylor
  * @date   04 Jan 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* start includes code */

#include "pressure_sensor.h"
#include "input_registers.h"

/* end includes code */

/* start macros code */

#define N_INPUT_REGISTERS 1

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_reading(sized_array_t * dest);

static pt_read_t read_handlers[N_INPUT_REGISTERS] = {
    read_reading,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=0,
};

void
input_registers_create(PrimaryTable base, Device device)
{
    base->vtable = &interface;
    self.base = device;

    /* start create code */

    /* end create code */
}

/**
 * @brief reads reading
 * @param dest Array to store results into.
 **/
static inline void
read_reading(sized_array_t * dest)
{
    /* start read_reading code */
    dest->size = 3;
    dest->bytes[0] = 2;
    uint16_t val = adc_average(self.base->hal->analog);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 1, val);
    /* end read_reading code */
}

