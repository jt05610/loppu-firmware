/**
  ******************************************************************************
  * @file   coils.c
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
#include "coils.h"

/* end includes code */

/* start macros code */

#define N_COILS 13

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_I_scale_analog(sized_array_t * dest);
static inline void write_I_scale_analog(uint16_t value);
static inline void read_internal_Rsense(sized_array_t * dest);
static inline void write_internal_Rsense(uint16_t value);
static inline void read_en_SpreadCycle(sized_array_t * dest);
static inline void write_en_SpreadCycle(uint16_t value);
static inline void read_shaft(sized_array_t * dest);
static inline void write_shaft(uint16_t value);
static inline void read_index_otpw(sized_array_t * dest);
static inline void write_index_otpw(uint16_t value);
static inline void read_index_step(sized_array_t * dest);
static inline void write_index_step(uint16_t value);
static inline void read_pdn_disable(sized_array_t * dest);
static inline void write_pdn_disable(uint16_t value);
static inline void read_mstep_reg_select(sized_array_t * dest);
static inline void write_mstep_reg_select(uint16_t value);
static inline void read_multistep_filt(sized_array_t * dest);
static inline void write_multistep_filt(uint16_t value);
static inline void read_test_mode(sized_array_t * dest);
static inline void write_test_mode(uint16_t value);
static inline void read_reset_flag(sized_array_t * dest);
static inline void write_reset_flag(uint16_t value);
static inline void read_drv_err_flag(sized_array_t * dest);
static inline void write_drv_err_flag(uint16_t value);
static inline void read_uv_cp_flag(sized_array_t * dest);
static inline void write_uv_cp_flag(uint16_t value);

static pt_read_t read_handlers[N_COILS] = {
    read_I_scale_analog,
    read_internal_Rsense,
    read_en_SpreadCycle,
    read_shaft,
    read_index_otpw,
    read_index_step,
    read_pdn_disable,
    read_mstep_reg_select,
    read_multistep_filt,
    read_test_mode,
    read_reset_flag,
    read_drv_err_flag,
    read_uv_cp_flag,
};

static pt_write_t write_handlers[N_COILS] = {
    write_I_scale_analog,
    write_internal_Rsense,
    write_en_SpreadCycle,
    write_shaft,
    write_index_otpw,
    write_index_step,
    write_pdn_disable,
    write_mstep_reg_select,
    write_multistep_filt,
    write_test_mode,
    write_reset_flag,
    write_drv_err_flag,
    write_uv_cp_flag,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
coils_create(PrimaryTable base, Device device)
{
    base->vtable = &interface;
    self.base = device;

    /* start create code */

    /* end create code */
}

/**
 * @brief reads I_scale_analog
 * @param dest Array to store results into.
 **/
static inline void
read_I_scale_analog(sized_array_t * dest)
{
    /* start read_I_scale_analog code */
    
    /* end read_I_scale_analog code */
}

/**
 * @brief writes I_scale_analog
 * @param value value to write to I_scale_analog.
 **/
static inline void
write_I_scale_analog(uint16_t value)
{
    /* start write_I_scale_analog code */
    
    /* end write_I_scale_analog code */
}


/**
 * @brief reads internal_Rsense
 * @param dest Array to store results into.
 **/
static inline void
read_internal_Rsense(sized_array_t * dest)
{
    /* start read_internal_Rsense code */
    
    /* end read_internal_Rsense code */
}

/**
 * @brief writes internal_Rsense
 * @param value value to write to internal_Rsense.
 **/
static inline void
write_internal_Rsense(uint16_t value)
{
    /* start write_internal_Rsense code */
    
    /* end write_internal_Rsense code */
}


/**
 * @brief reads en_SpreadCycle
 * @param dest Array to store results into.
 **/
static inline void
read_en_SpreadCycle(sized_array_t * dest)
{
    /* start read_en_SpreadCycle code */
    
    /* end read_en_SpreadCycle code */
}

/**
 * @brief writes en_SpreadCycle
 * @param value value to write to en_SpreadCycle.
 **/
static inline void
write_en_SpreadCycle(uint16_t value)
{
    /* start write_en_SpreadCycle code */
    
    /* end write_en_SpreadCycle code */
}


/**
 * @brief reads shaft
 * @param dest Array to store results into.
 **/
static inline void
read_shaft(sized_array_t * dest)
{
    /* start read_shaft code */
    
    /* end read_shaft code */
}

/**
 * @brief writes shaft
 * @param value value to write to shaft.
 **/
static inline void
write_shaft(uint16_t value)
{
    /* start write_shaft code */
    
    /* end write_shaft code */
}


/**
 * @brief reads index_otpw
 * @param dest Array to store results into.
 **/
static inline void
read_index_otpw(sized_array_t * dest)
{
    /* start read_index_otpw code */
    
    /* end read_index_otpw code */
}

/**
 * @brief writes index_otpw
 * @param value value to write to index_otpw.
 **/
static inline void
write_index_otpw(uint16_t value)
{
    /* start write_index_otpw code */
    
    /* end write_index_otpw code */
}


/**
 * @brief reads index_step
 * @param dest Array to store results into.
 **/
static inline void
read_index_step(sized_array_t * dest)
{
    /* start read_index_step code */
    
    /* end read_index_step code */
}

/**
 * @brief writes index_step
 * @param value value to write to index_step.
 **/
static inline void
write_index_step(uint16_t value)
{
    /* start write_index_step code */
    
    /* end write_index_step code */
}


/**
 * @brief reads pdn_disable
 * @param dest Array to store results into.
 **/
static inline void
read_pdn_disable(sized_array_t * dest)
{
    /* start read_pdn_disable code */
    
    /* end read_pdn_disable code */
}

/**
 * @brief writes pdn_disable
 * @param value value to write to pdn_disable.
 **/
static inline void
write_pdn_disable(uint16_t value)
{
    /* start write_pdn_disable code */
    
    /* end write_pdn_disable code */
}


/**
 * @brief reads mstep_reg_select
 * @param dest Array to store results into.
 **/
static inline void
read_mstep_reg_select(sized_array_t * dest)
{
    /* start read_mstep_reg_select code */
    
    /* end read_mstep_reg_select code */
}

/**
 * @brief writes mstep_reg_select
 * @param value value to write to mstep_reg_select.
 **/
static inline void
write_mstep_reg_select(uint16_t value)
{
    /* start write_mstep_reg_select code */
    
    /* end write_mstep_reg_select code */
}


/**
 * @brief reads multistep_filt
 * @param dest Array to store results into.
 **/
static inline void
read_multistep_filt(sized_array_t * dest)
{
    /* start read_multistep_filt code */
    
    /* end read_multistep_filt code */
}

/**
 * @brief writes multistep_filt
 * @param value value to write to multistep_filt.
 **/
static inline void
write_multistep_filt(uint16_t value)
{
    /* start write_multistep_filt code */
    
    /* end write_multistep_filt code */
}


/**
 * @brief reads test_mode
 * @param dest Array to store results into.
 **/
static inline void
read_test_mode(sized_array_t * dest)
{
    /* start read_test_mode code */
    
    /* end read_test_mode code */
}

/**
 * @brief writes test_mode
 * @param value value to write to test_mode.
 **/
static inline void
write_test_mode(uint16_t value)
{
    /* start write_test_mode code */
    
    /* end write_test_mode code */
}


/**
 * @brief reads reset_flag
 * @param dest Array to store results into.
 **/
static inline void
read_reset_flag(sized_array_t * dest)
{
    /* start read_reset_flag code */
    
    /* end read_reset_flag code */
}

/**
 * @brief writes reset_flag
 * @param value value to write to reset_flag.
 **/
static inline void
write_reset_flag(uint16_t value)
{
    /* start write_reset_flag code */
    
    /* end write_reset_flag code */
}


/**
 * @brief reads drv_err_flag
 * @param dest Array to store results into.
 **/
static inline void
read_drv_err_flag(sized_array_t * dest)
{
    /* start read_drv_err_flag code */
    
    /* end read_drv_err_flag code */
}

/**
 * @brief writes drv_err_flag
 * @param value value to write to drv_err_flag.
 **/
static inline void
write_drv_err_flag(uint16_t value)
{
    /* start write_drv_err_flag code */
    
    /* end write_drv_err_flag code */
}


/**
 * @brief reads uv_cp_flag
 * @param dest Array to store results into.
 **/
static inline void
read_uv_cp_flag(sized_array_t * dest)
{
    /* start read_uv_cp_flag code */
    
    /* end read_uv_cp_flag code */
}

/**
 * @brief writes uv_cp_flag
 * @param value value to write to uv_cp_flag.
 **/
static inline void
write_uv_cp_flag(uint16_t value)
{
    /* start write_uv_cp_flag code */
    
    /* end write_uv_cp_flag code */
}

