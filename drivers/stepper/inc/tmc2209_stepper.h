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

#include "stepper_driver.h"
#include "../../gpio/inc/gpio.h"
#include "../../serial/inc/serial.h"
#include "TMC2209.h"

typedef struct tmc2209_init_t
{
    Stepper base;
    GPIO gpio;
    Serial serial;
    TMC2209TypeDef * tmc2209;
    uint8_t channel;
    uint8_t slaveAddress;
    ConfigurationTypeDef *tmc2209_config;
    const int32_t *registerResetState;
} tmc2209_init_t;

void tmc2209_stepper_create(tmc2209_init_t * params);


#endif //INJECTOR_TMC2209_STEPPER_H
