/**
  ******************************************************************************
  * @file   discrete_inputs.c
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
#include "discrete_inputs.h"

/* end includes code */

/* start macros code */

#define N_DISCRETE_INPUTS 1

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_is_moving(sized_array_t * dest);

static pt_read_t read_handlers[N_DISCRETE_INPUTS] = {
    read_is_moving,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=0,
};

void
discrete_inputs_create(PrimaryTable base, Device device)
{
    base->vtable = &interface;
    self.base = device;
e
    /* start create code */

    /* end create code */
}

/**
 * @brief reads is_moving
 * @param dest Array to store results into.
 **/
static inline void
read_is_moving(sized_array_t * dest)
{
    /* start read_is_moving code */
    
    /* end read_is_moving code */
}

