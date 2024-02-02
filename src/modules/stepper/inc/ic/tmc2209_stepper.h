/**
  ******************************************************************************
  * @file   tmc2209_stepper.h
  * @author Jonathan Taylor
  * @date   11/17/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_TMC2209_STEPPER_H
#define INJECTOR_TMC2209_STEPPER_H

#include "stepper.h"
#include "peripherals.h"


typedef struct tmc2209_init_t {
    Peripherals hal;
    void *tim_inst;
    void *uart_inst;
    void *gpio_inst;
    gpio_pin_t en_pin;
    gpio_pin_t step_pin;
    gpio_pin_t dir_pin;
    bool inverse_dir;
    gpio_pin_t limit_pin;
    int32_t sg_thresh;
    int32_t cs_thresh;
} tmc2209_init_t;

Stepper tmc2209_stepper_create(const tmc2209_init_t *params);

int32_t tmc2209_sg_result();

uint8_t tmc2209_stepper_msg_count();

void tmc2209_set_mstep_reg(uint8_t reg);

void tmc2209_set_cs_thresh_vel(int32_t vel);

void tmc2209_set_sg_thresh(int32_t val);

int32_t tmc2209_tstep_result();

void tmc2209_set_t_pwm_thresh(int32_t val);

void tmc2209_set_spreadcycle(bool value);

void tmc2209_set_internal_r_sense(bool value);

void tmc2209_set_pdn_disable(bool value);

#endif //INJECTOR_TMC2209_STEPPER_H
