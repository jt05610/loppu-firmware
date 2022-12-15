/**
  ******************************************************************************
  * @file   holding_registers.c
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
#include "holding_registers.h"

/* end includes code */


/* start macros code */

#define N_HOLDING_REGISTERS 4

/* end macros code */


/* start struct code */

static struct {
    void * device;
} self = {0};

/* end struct code */


static inline void read_velocity(void * device, sized_array_t * dest);
static inline void write_velocity(void * device, uint16_t value);
static inline void read_target_position(void * device, sized_array_t * dest);
static inline void write_target_position(void * device, uint16_t value);
static inline void read_steps_per_mm(void * device, sized_array_t * dest);
static inline void write_steps_per_mm(void * device, uint16_t value);
static inline void read_nudge_increment(void * device, sized_array_t * dest);
static inline void write_nudge_increment(void * device, uint16_t value);

static pt_read_t read_handlers[N_HOLDING_REGISTERS] = {
    read_velocity,
    read_target_position,
    read_steps_per_mm,
    read_nudge_increment,
};

static pt_write_t write_handlers[N_HOLDING_REGISTERS] = {
    write_velocity,
    write_target_position,
    write_steps_per_mm,
    write_nudge_increment,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
holding_registers_create(PrimaryTable base, void * device)
{
    base->vtable = &interface;
    base->device = device;

    /* start create code */

    /* end create code */
}
static inline void
read_velocity(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_velocity code */
    
    /* end read_velocity code */
}

static inline void
write_velocity(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_velocity code */
    
    /* end write_velocity code */
}

static inline void
read_target_position(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_target_position code */
    
    /* end read_target_position code */
}

static inline void
write_target_position(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_target_position code */
    
    /* end write_target_position code */
}

static inline void
read_steps_per_mm(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_steps_per_mm code */
    
    /* end read_steps_per_mm code */
}

static inline void
write_steps_per_mm(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_steps_per_mm code */
    
    /* end write_steps_per_mm code */
}

static inline void
read_nudge_increment(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_nudge_increment code */
    
    /* end read_nudge_increment code */
}

static inline void
write_nudge_increment(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_nudge_increment code */
    
    /* end write_nudge_increment code */
}

