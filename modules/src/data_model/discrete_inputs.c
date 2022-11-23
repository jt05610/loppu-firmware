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



uint16_t get_btn_forward(GPIO gpio);

uint16_t get_btn_backward(GPIO gpio);

uint16_t get_btn_inject(GPIO gpio);

static discrete_input_getter getters[N_DISCRETE_INPUTS] = {
        get_btn_forward,
        get_btn_backward,
        get_btn_inject
};

void discrete_inputs_create(DiscreteInputs base, GPIO gpio)
{
    base->getters = getters;
    base->gpio = gpio;
}

uint16_t
discrete_inputs_read(DiscreteInputs base, uint16_t address)
{
    return base->getters[address](base->gpio);
}

inline uint16_t
get_btn_forward(GPIO gpio)
{
    return gpio_read_pin(gpio, BTN_FORWARD_PORT, BTN_FORWARD_PIN);
}

inline uint16_t
get_btn_backward(GPIO gpio)
{
    return gpio_read_pin(gpio, BTN_BACKWARD_PORT, BTN_BACKWARD_PIN);
}

inline uint16_t
get_btn_inject(GPIO gpio)
{
    return gpio_read_pin(gpio, BTN_INJECT_PORT, BTN_INJECT_PIN);
}
