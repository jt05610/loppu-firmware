/**
  ******************************************************************************
  * @file   discrete_inputs.h
  * @author Jonathan Taylor
  * @date   11/19/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_DISCRETE_INPUTS_H
#define INJECTOR_DISCRETE_INPUTS_H

#include <stdint-gcc.h>
#include "gpio/gpio.h"

#define N_DISCRETE_INPUTS 3

#define BTN_INJECT_PORT GPIO_PORT_A
#define BTN_INJECT_PIN 7

#define BTN_BACKWARD_PORT GPIO_PORT_A
#define BTN_BACKWARD_PIN 0

#define BTN_FORWARD_PORT GPIO_PORT_A
#define BTN_FORWARD_PIN 1

typedef struct discrete_inputs_t * DiscreteInputs;

typedef uint16_t (* discrete_input_getter)(GPIO gpio);

typedef struct discrete_inputs_t {
    GPIO gpio;
    discrete_input_getter * getters;
} discrete_inputs_t;

void discrete_inputs_create(DiscreteInputs base, GPIO gpio);

uint16_t discrete_inputs_read(DiscreteInputs base, uint16_t address);

#endif //INJECTOR_DISCRETE_INPUTS_H
