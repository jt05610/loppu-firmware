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
#include "gpio.h"

#define N_DISCRETE_INPUTS 3

typedef struct DiscreteInputsStruct discrete_inputs_t;

typedef struct discrete_inputs_t * DiscreteInputs;

typedef uint16_t (* discrete_input_getter)(GPIO gpio);

void discrete_inputs_create(DiscreteInputs base, GPIO gpio);

void discrete_inputs_handle(DiscreteInputs base, uint16_t address);

#endif //INJECTOR_DISCRETE_INPUTS_H
