/**
  ******************************************************************************
  * @file   discrete_inputs.c
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
#include "discrete_inputs.h"

/* end includes code */


/* start macros code */

#define N_DISCRETE_INPUTS 3

/* end macros code */


/* start struct code */

static struct {
    void * device;
} self = {0};

/* end struct code */


static inline void read_btn_forward(void * device, sized_array_t * dest);
static inline void write_btn_forward(void * device, uint16_t value);
static inline void read_btn_backward(void * device, sized_array_t * dest);
static inline void write_btn_backward(void * device, uint16_t value);
static inline void read_btn_inject(void * device, sized_array_t * dest);
static inline void write_btn_inject(void * device, uint16_t value);

static pt_read_t read_handlers[N_DISCRETE_INPUTS] = {
    read_btn_forward,
    read_btn_backward,
    read_btn_inject,
};

static pt_write_t write_handlers[N_DISCRETE_INPUTS] = {
    write_btn_forward,
    write_btn_backward,
    write_btn_inject,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
discrete_inputs_create(PrimaryTable base, void * device)
{
    base->vtable = &interface;
    base->device = device;

    /* start create code */

    /* end create code */
}
static inline void
read_btn_forward(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_btn_forward code */
    
    /* end read_btn_forward code */
}

static inline void
write_btn_forward(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_btn_forward code */
    
    /* end write_btn_forward code */
}

static inline void
read_btn_backward(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_btn_backward code */
    
    /* end read_btn_backward code */
}

static inline void
write_btn_backward(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_btn_backward code */
    
    /* end write_btn_backward code */
}

static inline void
read_btn_inject(void * device, sized_array_t * dest)
{
    NeedlePositioner d = (NeedlePositioner) device;
    /* start read_btn_inject code */
    
    /* end read_btn_inject code */
}

static inline void
write_btn_inject(void * device, uint16_t value)
{
    NeedlePositioner d = (NeedlePositioner) device;

    /* start write_btn_inject code */
    
    /* end write_btn_inject code */
}

