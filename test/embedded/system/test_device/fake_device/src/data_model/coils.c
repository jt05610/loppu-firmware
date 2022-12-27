/**
  ******************************************************************************
  * @file   coils.c
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
#include "coils.h"

/* end includes code */


/* start macros code */

#define N_COILS 5

/* end macros code */


/* start struct code */

static struct {
    void * device;
} self = {0};

/* end struct code */


static inline void read_home(void * device, sized_array_t * dest);
static inline void write_home(void * device, uint16_t value);
static inline void read_go_to_target(void * device, sized_array_t * dest);
static inline void write_go_to_target(void * device, uint16_t value);
static inline void read_stop(void * device, sized_array_t * dest);
static inline void write_stop(void * device, uint16_t value);
static inline void read_nudge(void * device, sized_array_t * dest);
static inline void write_nudge(void * device, uint16_t value);
static inline void read_zero(void * device, sized_array_t * dest);
static inline void write_zero(void * device, uint16_t value);

static pt_read_t read_handlers[N_COILS] = {
    read_home,
    read_go_to_target,
    read_stop,
    read_nudge,
    read_zero,
};

static pt_write_t write_handlers[N_COILS] = {
    write_home,
    write_go_to_target,
    write_stop,
    write_nudge,
    write_zero,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
coils_create(PrimaryTable base, void * device)
{
    base->vtable = &interface;
    base->device = device;

    /* start create code */

    /* end create code */
}
static inline void
read_home(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_home code */
    
    /* end read_home code */
}

static inline void
write_home(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_home code */
    
    /* end write_home code */
}

static inline void
read_go_to_target(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_go_to_target code */
    
    /* end read_go_to_target code */
}

static inline void
write_go_to_target(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_go_to_target code */
    
    /* end write_go_to_target code */
}

static inline void
read_stop(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_stop code */
    
    /* end read_stop code */
}

static inline void
write_stop(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_stop code */
    
    /* end write_stop code */
}

static inline void
read_nudge(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_nudge code */
    
    /* end read_nudge code */
}

static inline void
write_nudge(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_nudge code */
    
    /* end write_nudge code */
}

static inline void
read_zero(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_zero code */
    
    /* end read_zero code */
}

static inline void
write_zero(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_zero code */
    
    /* end write_zero code */
}

