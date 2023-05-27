/**
  ******************************************************************************
  * @file   input_registers.c
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
#include "input_registers.h"
#include "ic/tmc2209_stepper.h"

/* end includes code */

/* start macros code */

#define N_INPUT_REGISTERS 3

/* end macros code */

/* start struct code */

static struct
{
    Device base;
    Axis   axis;

} self = {0};

/* end struct code */

static inline void read_pos(sized_array_t * dest);

static inline void read_vel(sized_array_t * dest);

static inline void read_tstep(sized_array_t * dest);

static pt_read_t read_handlers[N_INPUT_REGISTERS] = {
        read_pos,
        read_vel,
        read_tstep
};

static primary_table_interface_t interface = {
        .read=read_handlers,
        .write=0,
};

void
input_registers_create(PrimaryTable base, Device device, Axis axis)
{
    base->vtable = &interface;
    self.base    = device;

    /* start create code */
    self.axis = axis;
    /* end create code */
}

/**
 * @brief reads pos
 * @param dest Array to store results into.
 **/
static inline void
read_pos(sized_array_t * dest)
{
    /* start read_pos code */
    uint16_t pos = axis_current_pos(self.axis);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 2, pos);
    dest->size = 4;
    /* end read_pos code */
}


/**
 * @brief reads vel
 * @param dest Array to store results into.
 **/
static inline void
read_vel(sized_array_t * dest)
{
    /* start read_vel code */
    uint16_t vel = axis_current_vel(self.axis);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 2, vel);
    dest->size = 4;
    /* end read_vel code */
}

/**
 * @brief reads tstep
 * @param dest Array to store results into.
 **/
static inline void
read_tstep(sized_array_t * dest)
{
    /* start read_vel code */
    uint16_t tstep = tmc2209_tstep_result();
    UINT16_TO_UINT8_ARRAY(dest->bytes, 2, tstep);
    dest->size = 4;
    /* end read_vel code */
}

