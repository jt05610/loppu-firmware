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

#define BTN_INJECT_PORT GPIO_PORT_A
#define BTN_INJECT_PIN 7

#define BTN_BACKWARD_PORT GPIO_PORT_A
#define BTN_BACKWARD_PIN 0

#define BTN_FORWARD_PORT GPIO_PORT_A
#define BTN_FORWARD_PIN 1

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
    base->gpio = gpio;
}

uint16_t
discrete_inputs_handle(DiscreteInputs base, uint16_t address)
{
    return base->getters[address](base->gpio);
}

static inline uint16_t
get_btn_forward(GPIO gpio)
{
    return gpio_read_pin(gpio, BTN_FORWARD_PORT, BTN_FORWARD_PIN);
}

static inline uint16_t
get_btn_backward(GPIO gpio)
{
    return gpio_read_pin(gpio, BTN_BACKWARD_PORT, BTN_BACKWARD_PIN);
}

static inline uint16_t
get_btn_inject(GPIO gpio)
{
    return gpio_read_pin(gpio, BTN_INJECT_PORT, BTN_INJECT_PIN);
}
