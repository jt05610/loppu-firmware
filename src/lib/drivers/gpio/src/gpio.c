//
// Created by Jonathan Taylor on 4/25/22.
//

#include "gpio.h"

void
gpio_set_pin(GPIO base, gpio_port_t port, gpio_pin_t pin)
{

    if (base && base->vtable && base->vtable->set_pin)
        base->vtable->set_pin(port, pin);
}

void
gpio_reset_pin(GPIO base, gpio_port_t port, gpio_pin_t pin)
{

    if (base && base->vtable && base->vtable->reset_pin)
        base->vtable->reset_pin(port, pin);
}

uint32_t
gpio_read_port(GPIO base, gpio_port_t port)
{
    uint32_t ret = 0;
    if (base && base->vtable && base->vtable->read_port)
        ret = base->vtable->read_port(port);
    return ret;
}

uint8_t
gpio_read_pin(GPIO base, gpio_port_t port, gpio_pin_t pin)
{

    uint8_t ret = 0;
    if (base && base->vtable && base->vtable->read_pin)
        ret = base->vtable->read_pin(port, pin);
    return ret;
}

void
gpio_write_port(GPIO base, gpio_port_t port, uint32_t value)
{
    if (base && base->vtable && base->vtable->write_port)
        base->vtable->write_port(port, value);
}

void
gpio_toggle(GPIO base, gpio_port_t port, gpio_pin_t pin)
{
    if (base && base->vtable && base->vtable->toggle)
        base->vtable->toggle(port, pin);
}