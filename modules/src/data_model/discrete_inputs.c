/**
  ******************************************************************************
  * @file   discrete_inputs.c
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

#include "data_model/discrete_inputs.h"
#include "gpio/gpio.h"

typedef struct discrete_inputs_t {
    GPIO gpio;
    discrete_input_getter * getters;
} DiscreteInputsStruct;

static inline uint16_t get_btn_forward(GPIO gpio);

static inline uint16_t get_btn_backward(GPIO gpio);

static inline uint16_t get_btn_inject(GPIO gpio);

static discrete_input_getter getters[N_DISCRETE_INPUTS] = {
        get_btn_forward,
        get_btn_backward,
        get_btn_inject
};

void discrete_inputs_create(DiscreteInputs base, GPIO gpio)
{
    base->getters = getters;
}

static inline uint16_t
get_btn_forward(GPIO gpio)
{

}

static inline uint16_t
get_btn_backward(GPIO gpio)
{

}

static inline uint16_t
get_btn_inject(GPIO gpio)
{

}
