#ifndef __STM32_GPIO_H__
#define __STM32_GPIO_H__

#include "stm32g0xx_it.h"
#include "gpio/gpio.h"

#define STM_PORT(port) \
((port) == GPIO_PORT_A) ? GPIOA : (((port) == GPIO_PORT_B) ? GPIOB : GPIOC)

typedef uint8_t port_mode_t;

typedef void (*handler_t)(void);

typedef enum pin_type_t
{
    NormalPin,
    InterruptPin

} pin_type_t;

typedef struct pin_init_t
{
    pin_type_t  type;
    gpio_port_t port;
    gpio_pin_t  pin_mask;
    port_mode_t mode;
    uint8_t     trigger;
    handler_t   handler;
} pin_init_t;

void stm32_gpio_create(GPIO base);

void stm32_gpio_init_pin(pin_init_t * init);

#endif /*__STM32_GPIO_H__ */

