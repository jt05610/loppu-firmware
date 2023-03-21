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
#include "holding_registers.h"

/* end includes code */

/* start macros code */

#define N_HOLDING_REGISTERS 2

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_target_vel(sized_array_t * dest);
static inline void write_target_vel(uint16_t value);
static inline void read_target_pos(sized_array_t * dest);
static inline void write_target_pos(uint16_t value);

static pt_read_t read_handlers[N_HOLDING_REGISTERS] = {
    read_target_vel,
    read_target_pos,
};

static pt_write_t write_handlers[N_HOLDING_REGISTERS] = {
    write_target_vel,
    write_target_pos,
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
e
    /* start create code */

    /* end create code */
}

/**
 * @brief reads target_vel
 * @param dest Array to store results into.
 **/
static inline void
read_target_vel(sized_array_t * dest)
{
    /* start read_target_vel code */
    
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
    
    /* end write_target_vel code */
}


/**
 * @brief reads target_pos
 * @param dest Array to store results into.
 **/
static inline void
read_target_pos(sized_array_t * dest)
{
    /* start read_target_pos code */
    
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
    
    /* end write_target_pos code */
}

