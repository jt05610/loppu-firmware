/**
  ******************************************************************************
  * @file   stm32_gpio.c
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32_gpio.h"
#include "default/gpio_config.h"
#include "stm32g0xx_ll_gpio.h"

static inline void set_pin(gpio_port_t port, gpio_pin_t pin);

static inline void reset_pin(gpio_port_t port, gpio_pin_t pin);

static inline uint32_t read_port(gpio_port_t port);

static inline uint8_t read_pin(gpio_port_t port, gpio_pin_t pin);

static inline void write_port(gpio_port_t port, uint32_t value);

static inline void toggle(gpio_port_t port, gpio_pin_t pin);

static inline void init_usart(LL_GPIO_InitTypeDef * p);

static inline void init_timers(LL_GPIO_InitTypeDef * p);

static inline void init_adc(LL_GPIO_InitTypeDef * p);

static inline void init_gpio(LL_GPIO_InitTypeDef * p);

static gpio_interface_t interface = {
        .set_pin = set_pin,
        .reset_pin = reset_pin,
        .read_port = read_port,
        .read_pin = read_pin,
        .write_port = write_port,
        .toggle = toggle
};

static struct
{
    gpio_t base;
} self = {0};

GPIO
stm32_gpio_create()
{
    self.base.vtable = &interface;
    LL_GPIO_InitTypeDef init;
    init_gpio(&init);
    init_adc(&init);
    init_usart(&init);
    init_timers(&init);
    return &self.base;
}

static inline void
init_gpio(LL_GPIO_InitTypeDef * p)
{
    p->Pin  = LL_GPIO_PIN_1;
    p->Mode = LL_GPIO_MODE_OUTPUT;
    p->Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOA, p);
}

static inline void
init_adc(LL_GPIO_InitTypeDef * p)
{
    p->Pin  = LL_GPIO_PIN_0;
    p->Mode = LL_GPIO_MODE_ANALOG;
    p->Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOA, p);
}

static inline void
init_usart(LL_GPIO_InitTypeDef * p)
{
#if STM32_ENABLE_USART1
    p->Pin        = STM32_USART1_RX_PIN;
    p->Mode       = LL_GPIO_MODE_ALTERNATE;
    p->Speed      = LL_GPIO_SPEED_FREQ_LOW;
    p->OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    p->Pull       = LL_GPIO_PULL_NO;
    p->Alternate  = LL_GPIO_AF_0;
    LL_GPIO_Init(STM32_USART1_RX_PORT, p);

    p->Pin = STM32_USART1_TX_PIN;
    LL_GPIO_Init(STM32_USART1_TX_PORT, p);

#if STM32_USART1_RS485
    p->Pin       = STM32_USART1_DE_PIN;
    p->Alternate = LL_GPIO_AF_1;
    LL_GPIO_Init(STM32_USART1_DE_PORT, p);

    p->Pin       = STM32_USART1_RE_PIN;
    p->Mode      = LL_GPIO_MODE_OUTPUT;
    p->Alternate = 0;
    LL_GPIO_Init(STM32_USART1_DE_PORT, p);
#endif // STM32_USART1_RS485

#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
    p->Pin        = STM32_USART2_RX_PIN;
    p->Mode       = LL_GPIO_MODE_ALTERNATE;
    p->Speed      = LL_GPIO_SPEED_FREQ_LOW;
    p->OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    p->Pull       = LL_GPIO_PULL_NO;
    p->Alternate  = LL_GPIO_AF_0;
    LL_GPIO_Init(STM32_USART2_RX_PORT, p);

    p->Pin = STM32_USART2_TX_PIN;
    LL_GPIO_Init(STM32_USART2_TX_PORT, p);

#if STM32_USART2_RS485
    p->Pin       = STM32_USART2_DE_PIN;
    p->Alternate = LL_GPIO_AF_1;
    LL_GPIO_Init(STM32_USART2_DE_PORT, p);

    p->Pin       = STM32_USART2_RE_PIN;
    p->Mode      = LL_GPIO_MODE_OUTPUT;
    p->Alternate = 0;
    LL_GPIO_Init(STM32_USART2_DE_PORT, p);
#endif // STM32_USART2_RS485

#endif //STM32_ENABLE_USART2
}

static inline void
init_timers(LL_GPIO_InitTypeDef * p)
{

}

#define STM_PORT(port) \
((port) == GPIO_PORT_A) ? GPIOA : (((port) == GPIO_PORT_B) ? GPIOB : GPIOC)

static inline void
set_pin(gpio_port_t port, gpio_pin_t pin)
{
    LL_GPIO_SetOutputPin(STM_PORT(port), pin);
}

static inline void
reset_pin(gpio_port_t port, gpio_pin_t pin)
{
    LL_GPIO_ResetOutputPin(STM_PORT(port), pin);
}

static inline uint32_t
read_port(gpio_port_t port)
{
    return LL_GPIO_ReadInputPort(STM_PORT(port));
}

static inline uint8_t
read_pin(gpio_port_t port, gpio_pin_t pin)
{
    return LL_GPIO_IsOutputPinSet(STM_PORT(port), pin);
}

static inline void
write_port(gpio_port_t port, uint32_t value)
{
    LL_GPIO_WriteOutputPort(STM_PORT(port), value);
}

static inline void
toggle(gpio_port_t port, gpio_pin_t pin)
{
    LL_GPIO_TogglePin(STM_PORT(port), pin);
}


