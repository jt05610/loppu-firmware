/**
  ******************************************************************************
  * @file   holding_registers.c
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
#include "stepdir.h"
#include "holding_registers.h"

/* end includes code */

/* start macros code */

#define N_HOLDING_REGISTERS 3

/* end macros code */

/* start struct code */


static struct
{
    Device base;
    Axis axis;
    StepDir stepdir;

} self = {0};

/* end struct code */

static inline void read_target_pos(sized_array_t * dest);

static inline void write_target_pos(uint16_t value);

static inline void read_target_vel(sized_array_t * dest);

static inline void write_target_vel(uint16_t value);

static inline void read_move_to(sized_array_t * dest);

static inline void write_move_to(uint16_t value);

static pt_read_t read_handlers[N_HOLDING_REGISTERS] = {
        read_target_pos,
        read_target_vel,
        read_move_to,
};

static pt_write_t write_handlers[N_HOLDING_REGISTERS] = {
        write_target_pos,
        write_target_vel,
        write_move_to,
};

static primary_table_interface_t interface = {
        .read=read_handlers,
        .write=write_handlers,
};

void
holding_registers_create(
        PrimaryTable base, Device device, StepDir stepdir, Axis axis)
{
    base->vtable = &interface;
    self.base    = device;

    /* start create code */
    self.stepdir = stepdir;
    self.axis = axis;
    /* end create code */
}

/**
 * @brief reads target_pos
 * @param dest Array to store results into.
 **/
static inline void
read_target_pos(sized_array_t * dest)
{
    /* start read_target_pos code */

    uint32_t v = stepdir_get_target_pos(self.stepdir);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 0, v);
    /* end read_target_pos code */
}

/**
 * @brief writes target_pos
 * @param value value to write to target_pos.
 **/
static inline void
write_target_pos(uint16_t value)
{
    /* start write_target_pos code */
    stepdir_move_to(self.stepdir, value);
    /* end write_target_pos code */
}


/**
 * @brief reads target_vel
 * @param dest Array to store results into.
 **/
static inline void
read_target_vel(sized_array_t * dest)
{
    /* start read_target_vel code */

    uint32_t v = stepdir_get_target_vel(self.stepdir);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 0, v);
    dest->size = 2;

    /* end read_target_vel code */
}

/**
 * @brief writes target_vel
 * @param value value to write to target_vel.
 **/
static inline void
write_target_vel(uint16_t value)
{
    /* start write_target_vel code */
    stepdir_set_vel_max(self.stepdir, value);
    /* end write_target_vel code */
}


/**
 * @brief reads move_to
 * @param dest Array to store results into.
 **/
static inline void
read_move_to(sized_array_t * dest)
{
    /* start read_move_to code */

    /* end read_move_to code */
}

/**
 * @brief writes move_to
 * @param value value to write to move_to.
 **/
static inline void
write_move_to(uint16_t value)
{
    /* start write_move_to code */
    axis_goto(self.axis, value, STEPDIR_MAX_VELOCITY);
    /* end write_move_to code */
}

