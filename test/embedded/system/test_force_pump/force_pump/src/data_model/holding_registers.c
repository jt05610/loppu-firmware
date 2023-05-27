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

#include "force_pump.h"
#include "linear_axis.h"
#include "holding_registers.h"
#include "ic/tmc2209_stepper.h"

#define UINT16_TO_UINT8_ARRAY(array, start, value)             \
    (array)[(start)]     = *((uint8_t *) &(value) + 1);       \
    (array)[(start) + 1] = *((uint8_t *) &(value) + 0)

/* end includes code */

/* start macros code */

#define N_HOLDING_REGISTERS 5

/* end macros code */

/* start struct code */

static struct
{
    Device base;
    Axis   axis;
} self = {0};

/* end struct code */

static inline void read_target_pos(sized_array_t * dest);

static inline void write_target_pos(uint16_t value);

static inline void read_target_vel(sized_array_t * dest);

static inline void write_target_vel(uint16_t value);

static inline void read_move_to(sized_array_t * dest);

static inline void write_move_to(uint16_t value);

static inline void read_accel(sized_array_t * dest);

static inline void write_accel(uint16_t value);

static inline void read_stallguard(sized_array_t * dest);

static inline void write_stallguard(uint16_t value);

static pt_read_t read_handlers[N_HOLDING_REGISTERS] = {
        read_target_pos,
        read_target_vel,
        read_move_to,
        read_accel,
        read_stallguard,

};

static pt_write_t write_handlers[N_HOLDING_REGISTERS] = {
        write_target_pos,
        write_target_vel,
        write_move_to,
        write_accel,
        write_stallguard,
};

static primary_table_interface_t interface = {
        .read=read_handlers,
        .write=write_handlers,
};

void
holding_registers_create(
        PrimaryTable base, Device device, Axis axis)
{
    base->vtable = &interface;
    self.base    = device;

    /* start create code */
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
    uint32_t v = axis_get_target_pos(self.axis);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 2, v);
    dest->size = 4;
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
    axis_set_target_pos(self.axis, value);
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

    uint16_t v = axis_get_target_vel(self.axis);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 2, v);
    dest->size = 4;

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
    axis_set_target_vel(self.axis, value);
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
    uint16_t v = axis_get_target_pos(self.axis) - axis_current_pos(self.axis);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 2, v);
    dest->size = 4;
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
    axis_goto(self.axis, value);
    /* end write_move_to code */
}

/**
 * @brief reads accel
 * @param dest Array to store results into.
 **/
static inline void
read_accel(sized_array_t * dest)
{
    /* start read_accel code */
    uint16_t v = axis_get_accel(self.axis);
    UINT16_TO_UINT8_ARRAY(dest->bytes, 2, v);
    dest->size = 4;
    /* end read_accel code */
}

/**
 * @brief writes accel
 * @param value value to write to accel.
 **/
static inline void
write_accel(uint16_t value)
{
    /* start write_accel code */
    axis_set_accel(self.axis, value);
    /* end write_accel code */
}

/**
 * @brief reads move_to
 * @param dest Array to store results into.
 **/
static inline void
read_stallguard(sized_array_t * dest)
{
    /* start read_stallguard code */
    uint16_t v = tmc2209_sg_result();
    UINT16_TO_UINT8_ARRAY(dest->bytes, 2, v);
    dest->size = 4;
    /* end read_stallguard code */
}

/**
 * @brief writes stallguard
 * @param value value to write to stallguard.
 **/
static inline void
write_stallguard(uint16_t value)
{
    /* start write_stallguard code */
    tmc2209_set_sg_thresh(value);
    /* end write_stallguard code */
}

