/**
  ******************************************************************************
  * @file   input_registers.c
  * @author Jonathan Taylor
  * @date   11 Dec 2022
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

/* start includes code */

#include "needle_positioner.h"
#include "input_registers.h"

/* end includes code */


/* start macros code */

#define N_INPUT_REGISTERS 3

/* end macros code */


/* start struct code */

static struct {
    void * device;
} self = {0};

/* end struct code */


static inline void read_current_position(void * device, sized_array_t * dest);
static inline void write_current_position(void * device, uint16_t value);
static inline void read_button_state(void * device, sized_array_t * dest);
static inline void write_button_state(void * device, uint16_t value);
static inline void read_current_velocity(void * device, sized_array_t * dest);
static inline void write_current_velocity(void * device, uint16_t value);

static pt_read_t read_handlers[N_INPUT_REGISTERS] = {
    read_current_position,
    read_button_state,
    read_current_velocity,
};

static pt_write_t write_handlers[N_INPUT_REGISTERS] = {
    write_current_position,
    write_button_state,
    write_current_velocity,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
input_registers_create(PrimaryTable base, void * device)
{
    base->vtable = &interface;
    base->device = device;

    /* start create code */

    /* end create code */
}
static inline void
read_current_position(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_current_position code */
    
    /* end read_current_position code */
}

static inline void
write_current_position(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_current_position code */
    
    /* end write_current_position code */
}

static inline void
read_button_state(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_button_state code */
    
    /* end read_button_state code */
}

static inline void
write_button_state(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_button_state code */
    
    /* end write_button_state code */
}

static inline void
read_current_velocity(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_current_velocity code */
    
    /* end read_current_velocity code */
}

static inline void
write_current_velocity(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_current_velocity code */
    
    /* end write_current_velocity code */
}

