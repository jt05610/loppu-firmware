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

#define N_COILS 6

/* end macros code */

/* start struct code */


static struct
{
    Device base;
    Axis   axis;

} self = {0};

/* end struct code */

static inline void read_start(sized_array_t * dest);

static inline void write_start(__attribute__((unused)) uint16_t value);

static inline void read_stop(sized_array_t * dest);

static inline void write_stop(__attribute__((unused)) uint16_t value);

static inline void read_home(sized_array_t * dest);

static inline void write_home(__attribute__((unused)) uint16_t value);

static inline void read_forward_stall(sized_array_t * dest);

static inline void write_forward_stall(__attribute__((unused)) uint16_t value);

static inline void read_zero(sized_array_t * dest);

static inline void write_zero(__attribute__((unused)) uint16_t value);

static inline void read_enable(sized_array_t * dest);

static inline void write_enable(uint16_t value);

static pt_read_t read_handlers[N_COILS] = {
        read_start,
        read_stop,
        read_home,
        read_forward_stall,
        read_zero,
        read_enable,
};

static pt_write_t write_handlers[N_COILS] = {
        write_start,
        write_stop,
        write_home,
        write_forward_stall,
        write_zero,
        write_enable,
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
    self.axis    = axis;
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
    dest->bytes[0] = 1;
    dest->bytes[1] = axis_is_moving(self.axis);
    dest->size = 2;
    /* end read_start code */
}

/**
 * @brief writes start
 * @param value value to write to start.
 **/
static inline void
write_start(__attribute__((unused)) uint16_t value)
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
    dest->bytes[0] = 1;
    dest->bytes[1] = !axis_is_moving(self.axis);
    dest->size = 2;

    /* end read_stop code */
}

/**
 * @brief writes stop
 * @param value value to write to stop.
 **/
static inline void
write_stop(__attribute__((unused)) uint16_t value)
{
    /* start write_stop code */
    axis_stop(self.axis);
    /* end write_stop code */
}


static inline void
read_home(sized_array_t * dest)
{
    dest->bytes[0] = 1;
    dest->bytes[1] = axis_homed(self.axis);
    dest->size = 2;
}

static inline void
write_home(__attribute__((unused)) uint16_t value)
{
    axis_home(self.axis);
}

static inline void
read_forward_stall(sized_array_t * dest)
{
    dest->bytes[0] = 1;
    dest->bytes[1] = !axis_is_moving(self.axis);
    dest->size = 2;
}

static inline void
write_forward_stall(__attribute__((unused)) uint16_t value)
{
    axis_forward_stall(self.axis);
}

static inline void
read_zero(sized_array_t * dest)
{
    dest->bytes[0] = 1;
    dest->bytes[1] = axis_homed(self.axis);
    dest->size = 2;
}

static inline void
write_zero(__attribute__((unused)) uint16_t value)
{
    axis_set_zero(self.axis);
}

static inline void
read_enable(sized_array_t * dest)
{
    dest->bytes[0] = 1;
    dest->bytes[1] = axis_get_enabled(self.axis);
    dest->size = 2;
}

static inline void
write_enable(uint16_t value)
{
    if (value > 0) {
        axis_set_enabled(self.axis, true);
    } else {
        axis_set_enabled(self.axis, false);
    }
}
