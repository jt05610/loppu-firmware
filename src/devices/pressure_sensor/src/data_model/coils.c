/**
  ******************************************************************************
  * @file   coils.c
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
#include "coils.h"

/* end includes code */

/* start macros code */

#define N_COILS 1

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_run(sized_array_t * dest);
static inline void write_run(uint16_t value);

static pt_read_t read_handlers[N_COILS] = {
    read_run,
};

static pt_write_t write_handlers[N_COILS] = {
    write_run,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
coils_create(PrimaryTable base, Device device)
{
    base->vtable = &interface;
    self.base = device;

    /* start create code */

    /* end create code */
}

/**
 * @brief reads run
 * @param dest Array to store results into.
 **/
static inline void
read_run(sized_array_t * dest)
{
    /* start read_run code */
    
    /* end read_run code */
}

/**
 * @brief writes run
 * @param value value to write to run.
 **/
static inline void
write_run(uint16_t value)
{
    /* start write_run code */
    if (value)
        adc_start(self.base->hal->analog);
    else
        adc_stop(self.base->hal->analog);
    /* end write_run code */
}
