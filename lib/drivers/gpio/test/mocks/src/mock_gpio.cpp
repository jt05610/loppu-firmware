//
// Created by Jonathan Taylor on 4/25/22.
//

#include "CppUTestExt/MockSupport.h"
#include "mock_gpio.h"

void
mock_gpio_expect_set_pin(gpio_port_t port, gpio_pin_t pin)
{
    mock().expectOneCall("set_pin")
            .withParameter("port", port)
            .withParameter("pin", pin);
}

void
mock_gpio_check_expectations()
{
    mock().checkExpectations();
}

void
mock_gpio_expect_reset_pin(gpio_port_t port, gpio_pin_t pin)
{
    mock().expectOneCall("reset_pin")
            .withParameter("port", port)
            .withParameter("pin", pin);
}

void
mock_gpio_expect_read_port(gpio_port_t port, uint32_t ret)
{
    mock().expectOneCall("read_port")
            .withParameter("port", port)
            .andReturnValue(ret);
}

void
mock_gpio_expect_read_pin(gpio_port_t port, gpio_pin_t pin, uint8_t ret)
{
    mock().expectOneCall("read_pin")
            .withParameter("port", port)
            .withParameter("pin", pin)
            .andReturnValue(ret);
}

void
mock_gpio_expect_write_port(gpio_port_t port, uint32_t value)
{
    mock().expectOneCall("write_port")
            .withParameter("port", port)
            .withParameter("value", value);
}

void
mock_gpio_expect_toggle(gpio_port_t port, gpio_pin_t pin)
{
    mock().expectOneCall("toggle")
            .withParameter("port", port)
            .withParameter("pin", pin);
}
