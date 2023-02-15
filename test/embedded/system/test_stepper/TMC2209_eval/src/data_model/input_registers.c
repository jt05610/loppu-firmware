/**
  ******************************************************************************
  * @file   input_registers.c
  * @author Jonathan Taylor
  * @date   14 Feb 2023
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

#include "tmc2209_eval.h"
#include "input_registers.h"

/* end includes code */

/* start macros code */

#define N_INPUT_REGISTERS 5

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_t_step(sized_array_t * dest);
static inline void read_stallguard_result(sized_array_t * dest);
static inline void read_microstep_count(sized_array_t * dest);
static inline void read_microstep_currentA(sized_array_t * dest);
static inline void read_microstep_currentB(sized_array_t * dest);

static pt_read_t read_handlers[N_INPUT_REGISTERS] = {
    read_t_step,
    read_stallguard_result,
    read_microstep_count,
    read_microstep_currentA,
    read_microstep_currentB,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=0,
};

void
input_registers_create(PrimaryTable base, Device device)
{
    base->vtable = &interface;
    self.base = device;

    /* start create code */

    /* end create code */
}

/**
 * @brief reads t_step
 * @param dest Array to store results into.
 **/
static inline void
read_t_step(sized_array_t * dest)
{
    /* start read_t_step code */
    
    /* end read_t_step code */
}


/**
 * @brief reads stallguard_result
 * @param dest Array to store results into.
 **/
static inline void
read_stallguard_result(sized_array_t * dest)
{
    /* start read_stallguard_result code */
    
    /* end read_stallguard_result code */
}


/**
 * @brief reads microstep_count
 * @param dest Array to store results into.
 **/
static inline void
read_microstep_count(sized_array_t * dest)
{
    /* start read_microstep_count code */
    
    /* end read_microstep_count code */
}


/**
 * @brief reads microstep_currentA
 * @param dest Array to store results into.
 **/
static inline void
read_microstep_currentA(sized_array_t * dest)
{
    /* start read_microstep_currentA code */
    
    /* end read_microstep_currentA code */
}


/**
 * @brief reads microstep_currentB
 * @param dest Array to store results into.
 **/
static inline void
read_microstep_currentB(sized_array_t * dest)
{
    /* start read_microstep_currentB code */
    
    /* end read_microstep_currentB code */
}

