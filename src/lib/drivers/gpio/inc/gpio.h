//
// Created by Jonathan Taylor on 4/25/22.
//

#ifndef DRIVERS_GPIO_H
#define DRIVERS_GPIO_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_GPIO_INTERRUPT_CALLBACKS 4

typedef struct gpio_t           * GPIO;
typedef struct gpio_interface_t * GPIOInterface;

typedef void * gpio_port_t;
typedef uint32_t gpio_pin_t;

#define GPIO_PIN_MODE_NORMAL 0x00
#define GPIO_PIN_MODE_PWM 0x01
#define GPIO_PIN_MODE_INTERRUPT 0x02
#define GPIO_PIN_MODE_ANALOG 0x03
#define GPIO_PIN_MODE_INPUT_CAP 0x04
#define GPIO_PIN_MODE_INPUT 0x05

void gpio_set_pin(GPIO base, gpio_port_t port, gpio_pin_t pin);

void gpio_reset_pin(GPIO base, gpio_port_t port, gpio_pin_t pin);

uint32_t gpio_read_port(GPIO base, gpio_port_t port);

uint8_t gpio_read_pin(GPIO base, gpio_port_t port, gpio_pin_t pin);

void gpio_write_port(GPIO base, gpio_port_t port, uint32_t value);

void gpio_toggle(GPIO base, gpio_port_t port, gpio_pin_t pin);

void gpio_init_pin(GPIO base, gpio_port_t port, gpio_pin_t pin, uint8_t mode);

void gpio_attach_cb(GPIO base, gpio_port_t port, gpio_pin_t pin, void (* cb)());

#include "gpio_private.h"

#endif //DRIVERS_GPIO_H
