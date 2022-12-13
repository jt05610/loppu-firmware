//
// Created by Jonathan Taylor on 4/25/22.
//

#ifndef VALVECONTROLLER_MOCKGPIO_H
#define VALVECONTROLLER_MOCKGPIO_H

extern "C"
{
#include "../../../inc/gpio.h"
}

void mock_gpio_expect_set_pin(gpio_port_t port, gpio_pin_t pin);

void mock_gpio_expect_reset_pin(gpio_port_t port, gpio_pin_t pin);

void mock_gpio_expect_read_port(gpio_port_t port, uint32_t ret);

void mock_gpio_expect_read_pin(gpio_port_t port, gpio_pin_t pin, uint8_t ret);

void mock_gpio_expect_write_port(gpio_port_t port, uint32_t value);

void mock_gpio_expect_toggle(gpio_port_t port, gpio_pin_t pin);

void mock_gpio_check_expectations();

#endif //VALVECONTROLLER_MOCKGPIO_H
