//
// Created by Jonathan Taylor on 4/25/22.
//

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "fake_gpio.h"
}

TEST_GROUP(FakeGPIO)
{
    gpio_t gpio;

    void setup() override
    {
        fake_gpio_create(&gpio);
    }

    void teardown() override
    {
    }
};

TEST(FakeGPIO, set_and_read_pin)
{
    gpio_port_t port = GPIO_PORT_A;
    gpio_pin_t  pin  = 5;
    gpio_set_pin(&gpio, port, pin);
    LONGS_EQUAL(1, gpio_read_pin(&gpio, port, pin));
}

TEST(FakeGPIO, reset_pin)
{
    gpio_port_t port = GPIO_PORT_B;
    gpio_pin_t  pin  = 2;
    gpio_set_pin(&gpio, port, pin);
    LONGS_EQUAL(1, gpio_read_pin(&gpio, port, pin));
    gpio_reset_pin(&gpio, port, pin);
    LONGS_EQUAL(0, gpio_read_pin(&gpio, port, pin));
}

TEST(FakeGPIO, write_and_read_port)
{
    gpio_port_t port       = GPIO_PORT_B;
    uint32_t    port_value = 0x00001234;
    gpio_write_port(&gpio, port, port_value);
    LONGS_EQUAL(port_value, gpio_read_port(&gpio, port));
}

TEST(FakeGPIO, toggle)
{
    gpio_port_t port = GPIO_PORT_A;
    gpio_pin_t  pin  = 2;
    gpio_toggle(&gpio, port, pin);
    LONGS_EQUAL(1, gpio_read_pin(&gpio, port, pin));
    gpio_toggle(&gpio, port, pin);
    LONGS_EQUAL(0, gpio_read_pin(&gpio, port, pin));
}