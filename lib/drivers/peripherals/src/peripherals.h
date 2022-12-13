/**
  ******************************************************************************
  * @file   peripherals.h
  * @author Jonathan Taylor
  * @date   12/12/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_PERIPHERALS_H
#define INJECTOR_PERIPHERALS_H

#include "serial.h"
#include "gpio.h"

typedef struct peripherals_t * Peripherals;

typedef struct peripherals_t {
    Serial serial;
    GPIO gpio;
} peripherals_t;

#endif //INJECTOR_PERIPHERALS_H
