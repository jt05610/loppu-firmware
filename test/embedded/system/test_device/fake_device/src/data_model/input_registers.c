/**
  ******************************************************************************
  * @file   input_registers.c
  * @author jtaylor
  * @date   03 Jan 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
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
   Device base;

} self = {0};

/* end struct code */

static inline void read_on_time(sized_array_t * dest);

static pt_read_t read_handlers[N_INPUT_REGISTERS] = {
    read_on_time,
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
 * @brief reads on_time
 * @param dest Array to store results into.
 **/
static inline void
read_on_time(sized_array_t * dest)
{
    /* start read_on_time code */
    
    /* end read_on_time code */
}

