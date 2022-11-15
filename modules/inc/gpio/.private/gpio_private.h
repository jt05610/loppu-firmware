//
// Created by Jonathan Taylor on 4/25/22.
//

#ifndef DRIVERS_GPIOPRIVATE_H
#define DRIVERS_GPIOPRIVATE_H

#include "gpio/gpio.h"

typedef struct gpio_interface_t
{
    void (* set_pin)(gpio_port_t port, gpio_pin_t pin);

    void (* reset_pin)(gpio_port_t port, gpio_pin_t pin);

    uint32_t (* read_port)(gpio_port_t port);

    uint8_t (* read_pin)(gpio_port_t port, gpio_pin_t pin);

    void (* write_port)(gpio_port_t port, uint32_t);

    void (* toggle)(gpio_port_t port, gpio_pin_t pin);

} gpio_interface_t;

typedef struct gpio_t
{
    GPIOInterface vtable;
} gpio_t;

#endif //DRIVERS_GPIOPRIVATE_H
