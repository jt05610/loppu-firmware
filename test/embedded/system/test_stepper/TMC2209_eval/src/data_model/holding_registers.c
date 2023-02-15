/**
  ******************************************************************************
  * @file   holding_registers.c
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
#include "holding_registers.h"

/* end includes code */

/* start macros code */

#define N_HOLDING_REGISTERS 12

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_send_delay(sized_array_t * dest);
static inline void write_send_delay(uint16_t value);
static inline void read_f_clk_trim(sized_array_t * dest);
static inline void write_f_clk_trim(uint16_t value);
static inline void read_ot_trim(sized_array_t * dest);
static inline void write_ot_trim(uint16_t value);
static inline void read_current_standstill(sized_array_t * dest);
static inline void write_current_standstill(uint16_t value);
static inline void read_current_motor_run(sized_array_t * dest);
static inline void write_current_motor_run(uint16_t value);
static inline void read_current_hold_delay(sized_array_t * dest);
static inline void write_current_hold_delay(uint16_t value);
static inline void read_t_powerdown(sized_array_t * dest);
static inline void write_t_powerdown(uint16_t value);
static inline void read_t_pwm_thresh(sized_array_t * dest);
static inline void write_t_pwm_thresh(uint16_t value);
static inline void read_v_actual(sized_array_t * dest);
static inline void write_v_actual(uint16_t value);
static inline void read_t_cool_thrs(sized_array_t * dest);
static inline void write_t_cool_thrs(uint16_t value);
static inline void read_stallguard_threshold(sized_array_t * dest);
static inline void write_stallguard_threshold(uint16_t value);
static inline void read_coolstep_conf(sized_array_t * dest);
static inline void write_coolstep_conf(uint16_t value);

static pt_read_t read_handlers[N_HOLDING_REGISTERS] = {
    read_send_delay,
    read_f_clk_trim,
    read_ot_trim,
    read_current_standstill,
    read_current_motor_run,
    read_current_hold_delay,
    read_t_powerdown,
    read_t_pwm_thresh,
    read_v_actual,
    read_t_cool_thrs,
    read_stallguard_threshold,
    read_coolstep_conf,
};

static pt_write_t write_handlers[N_HOLDING_REGISTERS] = {
    write_send_delay,
    write_f_clk_trim,
    write_ot_trim,
    write_current_standstill,
    write_current_motor_run,
    write_current_hold_delay,
    write_t_powerdown,
    write_t_pwm_thresh,
    write_v_actual,
    write_t_cool_thrs,
    write_stallguard_threshold,
    write_coolstep_conf,
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
 * @brief reads send_delay
 * @param dest Array to store results into.
 **/
static inline void
read_send_delay(sized_array_t * dest)
{
    /* start read_send_delay code */
    
    /* end read_send_delay code */
}

/**
 * @brief writes send_delay
 * @param value value to write to send_delay.
 **/
static inline void
write_send_delay(uint16_t value)
{
    /* start write_send_delay code */
    
    /* end write_send_delay code */
}


/**
 * @brief reads f_clk_trim
 * @param dest Array to store results into.
 **/
static inline void
read_f_clk_trim(sized_array_t * dest)
{
    /* start read_f_clk_trim code */
    
    /* end read_f_clk_trim code */
}

/**
 * @brief writes f_clk_trim
 * @param value value to write to f_clk_trim.
 **/
static inline void
write_f_clk_trim(uint16_t value)
{
    /* start write_f_clk_trim code */
    
    /* end write_f_clk_trim code */
}


/**
 * @brief reads ot_trim
 * @param dest Array to store results into.
 **/
static inline void
read_ot_trim(sized_array_t * dest)
{
    /* start read_ot_trim code */
    
    /* end read_ot_trim code */
}

/**
 * @brief writes ot_trim
 * @param value value to write to ot_trim.
 **/
static inline void
write_ot_trim(uint16_t value)
{
    /* start write_ot_trim code */
    
    /* end write_ot_trim code */
}


/**
 * @brief reads current_standstill
 * @param dest Array to store results into.
 **/
static inline void
read_current_standstill(sized_array_t * dest)
{
    /* start read_current_standstill code */
    
    /* end read_current_standstill code */
}

/**
 * @brief writes current_standstill
 * @param value value to write to current_standstill.
 **/
static inline void
write_current_standstill(uint16_t value)
{
    /* start write_current_standstill code */
    
    /* end write_current_standstill code */
}


/**
 * @brief reads current_motor_run
 * @param dest Array to store results into.
 **/
static inline void
read_current_motor_run(sized_array_t * dest)
{
    /* start read_current_motor_run code */
    
    /* end read_current_motor_run code */
}

/**
 * @brief writes current_motor_run
 * @param value value to write to current_motor_run.
 **/
static inline void
write_current_motor_run(uint16_t value)
{
    /* start write_current_motor_run code */
    
    /* end write_current_motor_run code */
}


/**
 * @brief reads current_hold_delay
 * @param dest Array to store results into.
 **/
static inline void
read_current_hold_delay(sized_array_t * dest)
{
    /* start read_current_hold_delay code */
    
    /* end read_current_hold_delay code */
}

/**
 * @brief writes current_hold_delay
 * @param value value to write to current_hold_delay.
 **/
static inline void
write_current_hold_delay(uint16_t value)
{
    /* start write_current_hold_delay code */
    
    /* end write_current_hold_delay code */
}


/**
 * @brief reads t_powerdown
 * @param dest Array to store results into.
 **/
static inline void
read_t_powerdown(sized_array_t * dest)
{
    /* start read_t_powerdown code */
    
    /* end read_t_powerdown code */
}

/**
 * @brief writes t_powerdown
 * @param value value to write to t_powerdown.
 **/
static inline void
write_t_powerdown(uint16_t value)
{
    /* start write_t_powerdown code */
    
    /* end write_t_powerdown code */
}


/**
 * @brief reads t_pwm_thresh
 * @param dest Array to store results into.
 **/
static inline void
read_t_pwm_thresh(sized_array_t * dest)
{
    /* start read_t_pwm_thresh code */
    
    /* end read_t_pwm_thresh code */
}

/**
 * @brief writes t_pwm_thresh
 * @param value value to write to t_pwm_thresh.
 **/
static inline void
write_t_pwm_thresh(uint16_t value)
{
    /* start write_t_pwm_thresh code */
    
    /* end write_t_pwm_thresh code */
}


/**
 * @brief reads v_actual
 * @param dest Array to store results into.
 **/
static inline void
read_v_actual(sized_array_t * dest)
{
    /* start read_v_actual code */
    
    /* end read_v_actual code */
}

/**
 * @brief writes v_actual
 * @param value value to write to v_actual.
 **/
static inline void
write_v_actual(uint16_t value)
{
    /* start write_v_actual code */
    
    /* end write_v_actual code */
}


/**
 * @brief reads t_cool_thrs
 * @param dest Array to store results into.
 **/
static inline void
read_t_cool_thrs(sized_array_t * dest)
{
    /* start read_t_cool_thrs code */
    
    /* end read_t_cool_thrs code */
}

/**
 * @brief writes t_cool_thrs
 * @param value value to write to t_cool_thrs.
 **/
static inline void
write_t_cool_thrs(uint16_t value)
{
    /* start write_t_cool_thrs code */
    
    /* end write_t_cool_thrs code */
}


/**
 * @brief reads stallguard_threshold
 * @param dest Array to store results into.
 **/
static inline void
read_stallguard_threshold(sized_array_t * dest)
{
    /* start read_stallguard_threshold code */
    
    /* end read_stallguard_threshold code */
}

/**
 * @brief writes stallguard_threshold
 * @param value value to write to stallguard_threshold.
 **/
static inline void
write_stallguard_threshold(uint16_t value)
{
    /* start write_stallguard_threshold code */
    
    /* end write_stallguard_threshold code */
}


/**
 * @brief reads coolstep_conf
 * @param dest Array to store results into.
 **/
static inline void
read_coolstep_conf(sized_array_t * dest)
{
    /* start read_coolstep_conf code */
    
    /* end read_coolstep_conf code */
}

/**
 * @brief writes coolstep_conf
 * @param value value to write to coolstep_conf.
 **/
static inline void
write_coolstep_conf(uint16_t value)
{
    /* start write_coolstep_conf code */
    
    /* end write_coolstep_conf code */
}

