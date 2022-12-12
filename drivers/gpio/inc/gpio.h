//
// Created by Jonathan Taylor on 4/25/22.
//

#ifndef DRIVERS_GPIO_H
#define DRIVERS_GPIO_H

#include "../../modbus/inc/public/modbus/project_types.h"

typedef struct gpio_t           * GPIO;
typedef struct gpio_interface_t * GPIOInterface;

typedef enum gpio_port_t
{
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C

} gpio_port_t;

typedef uint32_t gpio_pin_t;

void gpio_set_pin(GPIO base, gpio_port_t port, gpio_pin_t pin);

void gpio_reset_pin(GPIO base, gpio_port_t port, gpio_pin_t pin);

uint32_t gpio_read_port(GPIO base, gpio_port_t port);

uint8_t gpio_read_pin(GPIO base, gpio_port_t port, gpio_pin_t pin);

void gpio_write_port(GPIO base, gpio_port_t port, uint32_t value);

void gpio_toggle(GPIO base, gpio_port_t port, gpio_pin_t pin);

#include ".private/gpio_private.h"

#endif //DRIVERS_GPIO_H
