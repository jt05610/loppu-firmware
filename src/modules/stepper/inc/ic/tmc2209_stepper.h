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


typedef struct tmc2209_init_t
{
    Peripherals hal;
    void * tim_inst;
    void * uart_inst;
    void * gpio_inst;
    gpio_pin_t en_pin;
    gpio_pin_t  step_pin;
    gpio_pin_t  dir_pin;
    bool inverse_dir;
    gpio_pin_t  limit_pin;
} tmc2209_init_t;

Stepper tmc2209_stepper_create(tmc2209_init_t * params);

uint8_t tmc2209_stepper_msg_count();

void tmc2209_set_mstep_reg(uint8_t reg);

#endif //INJECTOR_TMC2209_STEPPER_H
