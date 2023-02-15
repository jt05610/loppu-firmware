/**
  ******************************************************************************
  * @file   discrete_inputs.c
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
#include "discrete_inputs.h"

/* end includes code */

/* start macros code */

#define N_DISCRETE_INPUTS 9

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_en_state(sized_array_t * dest);
static inline void read_ms1_state(sized_array_t * dest);
static inline void read_ms2_state(sized_array_t * dest);
static inline void read_diag_state(sized_array_t * dest);
static inline void read_pdn_uart_state(sized_array_t * dest);
static inline void read_step_state(sized_array_t * dest);
static inline void read_spread_en_state(sized_array_t * dest);
static inline void read_dir_state(sized_array_t * dest);
static inline void read_diag_msg_cnt(sized_array_t * dest);

static pt_read_t read_handlers[N_DISCRETE_INPUTS] = {
    read_en_state,
    read_ms1_state,
    read_ms2_state,
    read_diag_state,
    read_pdn_uart_state,
    read_step_state,
    read_spread_en_state,
    read_dir_state,
    read_diag_msg_cnt,
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

    /* start create code */

    /* end create code */
}

/**
 * @brief reads en_state
 * @param dest Array to store results into.
 **/
static inline void
read_en_state(sized_array_t * dest)
{
    /* start read_en_state code */
    
    /* end read_en_state code */
}


/**
 * @brief reads ms1_state
 * @param dest Array to store results into.
 **/
static inline void
read_ms1_state(sized_array_t * dest)
{
    /* start read_ms1_state code */
    
    /* end read_ms1_state code */
}


/**
 * @brief reads ms2_state
 * @param dest Array to store results into.
 **/
static inline void
read_ms2_state(sized_array_t * dest)
{
    /* start read_ms2_state code */
    
    /* end read_ms2_state code */
}


/**
 * @brief reads diag_state
 * @param dest Array to store results into.
 **/
static inline void
read_diag_state(sized_array_t * dest)
{
    /* start read_diag_state code */
    
    /* end read_diag_state code */
}


/**
 * @brief reads pdn_uart_state
 * @param dest Array to store results into.
 **/
static inline void
read_pdn_uart_state(sized_array_t * dest)
{
    /* start read_pdn_uart_state code */
    
    /* end read_pdn_uart_state code */
}


/**
 * @brief reads step_state
 * @param dest Array to store results into.
 **/
static inline void
read_step_state(sized_array_t * dest)
{
    /* start read_step_state code */
    
    /* end read_step_state code */
}


/**
 * @brief reads spread_en_state
 * @param dest Array to store results into.
 **/
static inline void
read_spread_en_state(sized_array_t * dest)
{
    /* start read_spread_en_state code */
    
    /* end read_spread_en_state code */
}


/**
 * @brief reads dir_state
 * @param dest Array to store results into.
 **/
static inline void
read_dir_state(sized_array_t * dest)
{
    /* start read_dir_state code */
    
    /* end read_dir_state code */
}


/**
 * @brief reads diag_msg_cnt
 * @param dest Array to store results into.
 **/
static inline void
read_diag_msg_cnt(sized_array_t * dest)
{
    /* start read_diag_msg_cnt code */
    
    /* end read_diag_msg_cnt code */
}

