//
// Created by Jonathan Taylor on 4/25/22.
//
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "mock_gpio_c.h"
}

#include "mock_gpio.h"

TEST_GROUP(MockGPIO)
{
    gpio_t gpio;

    void setup() override
    {
        mock_gpio_create(&gpio);
    }

    void teardown() override
    {
        mock_gpio_check_expectations();
        mock_gpio_destroy();
    }
};

TEST(MockGPIO, set_pin)
{
    gpio_port_t port = GPIO_PORT_A;
    gpio_pin_t  pin  = 3;
    mock_gpio_expect_set_pin(port, pin);
    gpio_set_pin(&gpio, port, pin);
}

TEST(MockGPIO, reset_pin)
{
    gpio_port_t port = GPIO_PORT_A;
    gpio_pin_t  pin  = 3;
    mock_gpio_expect_reset_pin(port, pin);
    gpio_reset_pin(&gpio, port, pin);
}

TEST(MockGPIO, read_port)
{
    gpio_port_t port       = GPIO_PORT_A;
    uint32_t    port_value = 0x0000abcd;
    mock_gpio_expect_read_port(port, port_value);
    uint32_t result = gpio_read_port(&gpio, port);
    LONGS_EQUAL(port_value, result);
}

TEST(MockGPIO, read_pin)
{
    gpio_port_t port      = GPIO_PORT_A;
    gpio_pin_t  pin       = 3;
    uint8_t     pin_value = 1;
    mock_gpio_expect_read_pin(port, pin, pin_value);
    uint8_t result = gpio_read_pin(&gpio, port, pin);
    LONGS_EQUAL(pin_value, result);
}

TEST(MockGPIO, write_port)
{
    gpio_port_t port       = GPIO_PORT_A;
    uint32_t    port_value = 0x0000abcd;
    mock_gpio_expect_write_port(port, port_value);
    gpio_write_port(&gpio, port, port_value);
}

TEST(MockGPIO, toggle)
{
    gpio_port_t port = GPIO_PORT_A;
    gpio_pin_t  pin  = 3;
    mock_gpio_expect_toggle(port, pin);
    gpio_toggle(&gpio, port, pin);
}
