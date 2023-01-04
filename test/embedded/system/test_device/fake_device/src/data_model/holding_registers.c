/**
  ******************************************************************************
  * @file   holding_registers.c
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
#include "holding_registers.h"

/* end includes code */

/* start macros code */

#define N_HOLDING_REGISTERS 1

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_blink_frequency(sized_array_t * dest);
static inline void write_blink_frequency(uint16_t value);

static pt_read_t read_handlers[N_HOLDING_REGISTERS] = {
    read_blink_frequency,
};

static pt_write_t write_handlers[N_HOLDING_REGISTERS] = {
    write_blink_frequency,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
holding_registers_create(PrimaryTable base, Device device)
{
    base->vtable = &interface;
    self.base = device;

    /* start create code */

    /* end create code */
}

/**
 * @brief reads blink_frequency
 * @param dest Array to store results into.
 **/
static inline void
read_blink_frequency(sized_array_t * dest)
{
    /* start read_blink_frequency code */
    
    /* end read_blink_frequency code */
}

/**
 * @brief writes blink_frequency
 * @param value value to write to blink_frequency.
 **/
static inline void
write_blink_frequency(uint16_t value)
{
    /* start write_blink_frequency code */
    
    /* end write_blink_frequency code */
}

