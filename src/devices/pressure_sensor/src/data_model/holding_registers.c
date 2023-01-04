/**
  ******************************************************************************
  * @file   holding_registers.c
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

static inline void read_cal_slope(sized_array_t * dest);
static inline void write_cal_slope(uint16_t value);
static inline void read_cal_intercept(sized_array_t * dest);
static inline void write_cal_intercept(uint16_t value);

static pt_read_t read_handlers[N_HOLDING_REGISTERS] = {
    read_cal_slope,
    read_cal_intercept,
};

static pt_write_t write_handlers[N_HOLDING_REGISTERS] = {
    write_cal_slope,
    write_cal_intercept,
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
 * @brief reads cal_slope
 * @param dest Array to store results into.
 **/
static inline void
read_cal_slope(sized_array_t * dest)
{
    /* start read_cal_slope code */
    
    /* end read_cal_slope code */
}

/**
 * @brief writes cal_slope
 * @param value value to write to cal_slope.
 **/
static inline void
write_cal_slope(uint16_t value)
{
    /* start write_cal_slope code */
    
    /* end write_cal_slope code */
}


/**
 * @brief reads cal_intercept
 * @param dest Array to store results into.
 **/
static inline void
read_cal_intercept(sized_array_t * dest)
{
    /* start read_cal_intercept code */
    
    /* end read_cal_intercept code */
}

/**
 * @brief writes cal_intercept
 * @param value value to write to cal_intercept.
 **/
static inline void
write_cal_intercept(uint16_t value)
{
    /* start write_cal_intercept code */
    
    /* end write_cal_intercept code */
}

