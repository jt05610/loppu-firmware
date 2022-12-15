//
// Created by Jonathan Taylor on 4/25/22.
//
#include "fake_gpio.h"

#define PORT_PINS 16
#define GPIO_PORTS 4

typedef struct fake_gpio_t * FakeGPIO;

static struct fake_gpio_t
{
    uint32_t ports[GPIO_PORTS];

} self = {};

static void fake_gpio_set_pin(gpio_port_t port, gpio_pin_t pin);

static void fake_gpio_reset_pin(gpio_port_t port, gpio_pin_t pin);

static uint32_t fake_gpio_read_port(gpio_port_t port);

static uint8_t fake_gpio_read_pin(gpio_port_t port, gpio_pin_t pin);

static void fake_gpio_write_port(gpio_port_t port, uint32_t value);

static void fake_gpio_toggle(gpio_port_t port, gpio_pin_t pin);

static gpio_interface_t fake_gpio_interface = {
        .set_pin = fake_gpio_set_pin,
        .reset_pin = fake_gpio_reset_pin,
        .read_port = fake_gpio_read_port,
        .read_pin = fake_gpio_read_pin,
        .write_port = fake_gpio_write_port,
        .toggle = fake_gpio_toggle
};

void
fake_gpio_create(GPIO base)
{
    base->vtable = &fake_gpio_interface;
}

void
fake_gpio_set_pin(gpio_port_t port, gpio_pin_t pin)
{
    if (pin < PORT_PINS)
        self.ports[port] |= 1UL << pin;
}

void
fake_gpio_reset_pin(gpio_port_t port, gpio_pin_t pin)
{
    if (pin < PORT_PINS)
        self.ports[port] &= ~(1UL << pin);
}

uint32_t
fake_gpio_read_port(gpio_port_t port)
{
    return self.ports[port];
}

uint8_t
fake_gpio_read_pin(gpio_port_t port, gpio_pin_t pin)
{
    uint8_t ret = 0xFF;
    if (pin < PORT_PINS)
        ret = (self.ports[port] >> pin) & 1U;
    return ret;
}

void
fake_gpio_write_port(gpio_port_t port, uint32_t value)
{
    self.ports[port] = value;
}

void
fake_gpio_toggle(gpio_port_t port, gpio_pin_t pin)
{
    if (pin < PORT_PINS)
        self.ports[port] ^= 1UL << pin;
}