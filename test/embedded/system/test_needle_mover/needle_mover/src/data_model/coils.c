/**
  ******************************************************************************
  * @file   coils.c
  * @author jtaylor
  * @date   21 Mar 2023
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

#include "needle_mover.h"
#include "coils.h"
#include "linear_axis.h"

/* end includes code */

/* start macros code */

#define N_COILS 2

/* end macros code */

/* start struct code */


static struct
{
    Device base;
    Axis   axis;

} self = {0};

/* end struct code */

static inline void read_start(sized_array_t * dest);

static inline void write_start(uint16_t value);

static inline void read_stop(sized_array_t * dest);

static inline void write_stop(uint16_t value);

static pt_read_t read_handlers[N_COILS] = {
        read_start,
        read_stop,
};

static pt_write_t write_handlers[N_COILS] = {
        write_start,
        write_stop,
};

static primary_table_interface_t interface = {
        .read=read_handlers,
        .write=write_handlers,
};

void
coils_create(PrimaryTable base, Device device, Axis axis)
{
    base->vtable = &interface;
    self.base    = device;
    self.axis = axis;
    /* start create code */

    /* end create code */
}

/**
 * @brief reads start
 * @param dest Array to store results into.
 **/
static inline void
read_start(sized_array_t * dest)
{
    /* start read_start code */
    /* end read_start code */
}

/**
 * @brief writes start
 * @param value value to write to start.
 **/
static inline void
write_start(uint16_t value)
{
    /* start write_start code */
    axis_start(self.axis);
    /* end write_start code */
}


/**
 * @brief reads stop
 * @param dest Array to store results into.
 **/
static inline void
read_stop(sized_array_t * dest)
{
    /* start read_stop code */
    axis_stop(self.axis);
    /* end read_stop code */
}

/**
 * @brief writes stop
 * @param value value to write to stop.
 **/
static inline void
write_stop(uint16_t value)
{
    /* start write_stop code */
    axis_stop(self.axis);
    /* end write_stop code */
}

