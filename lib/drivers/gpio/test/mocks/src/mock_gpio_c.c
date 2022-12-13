//
// Created by Jonathan Taylor on 4/25/22.
//

#include "CppUTestExt/MockSupport_c.h"

#include "mock_gpio_c.h"

static void mock_gpio_set_pin(gpio_port_t port, gpio_pin_t pin);

static void mock_gpio_reset_pin(gpio_port_t port, gpio_pin_t pin);

static uint32_t mock_gpio_read_port(gpio_port_t port);

static uint8_t mock_gpio_read_pin(gpio_port_t port, gpio_pin_t pin);

static void mock_gpio_write_port(gpio_port_t port, uint32_t value);

static void mock_gpio_toggle(gpio_port_t port, gpio_pin_t pin);

static gpio_interface_t mock_gpio_interface = {
        .set_pin = mock_gpio_set_pin,
        .reset_pin = mock_gpio_reset_pin,
        .read_port = mock_gpio_read_port,
        .read_pin = mock_gpio_read_pin,
        .write_port = mock_gpio_write_port,
        .toggle = mock_gpio_toggle
};

void
mock_gpio_create(GPIO base)
{
    base->vtable = &mock_gpio_interface;
}

void
mock_gpio_destroy()
{
    mock_c()->clear();
}

void
mock_gpio_set_pin(gpio_port_t port, gpio_pin_t pin)
{
    mock_c()->actualCall("set_pin")
            ->withLongIntParameters("port", port)
            ->withLongIntParameters("pin", pin);
}

void
mock_gpio_reset_pin(gpio_port_t port, gpio_pin_t pin)
{
    mock_c()->actualCall("reset_pin")
            ->withLongIntParameters("port", port)
            ->withLongIntParameters("pin", pin);
}

uint32_t
mock_gpio_read_port(gpio_port_t port)
{
    mock_c()->actualCall("read_port")
            ->withLongIntParameters("port", port);
    return mock_c()->returnValue().value.longIntValue;
}

uint8_t
mock_gpio_read_pin(gpio_port_t port, gpio_pin_t pin)
{
    mock_c()->actualCall("read_pin")
            ->withLongIntParameters("port", port)
            ->withLongIntParameters("pin", pin);
    return mock_c()->returnValue().value.intValue;
}

void mock_gpio_write_port(gpio_port_t port, uint32_t value)
{

    mock_c()->actualCall("write_port")
            ->withLongIntParameters("port", port)
            ->withLongIntParameters("value", value);
}

void mock_gpio_toggle(gpio_port_t port, gpio_pin_t pin)
{
    mock_c()->actualCall("toggle")
            ->withLongIntParameters("port", port)
            ->withLongIntParameters("pin", pin);
}