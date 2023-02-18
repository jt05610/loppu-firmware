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
#include "stm32g0xx_ll_exti.h"
#include "advanced/gpio_adv_config.h"
#include "stm32_interrupts.h"

static inline void set_pin(gpio_port_t port, gpio_pin_t pin);

static inline void init_pin(gpio_port_t port, gpio_pin_t pin, uint8_t pin_mode);

static inline void attach_cb(gpio_port_t port, gpio_pin_t pin, void (*cb)(), bool active_high);

static inline void reset_pin(gpio_port_t port, gpio_pin_t pin);

static inline uint32_t read_port(gpio_port_t port);

static inline uint8_t read_pin(gpio_port_t port, gpio_pin_t pin);

static inline void write_port(gpio_port_t port, uint32_t value);

static inline void toggle(gpio_port_t port, gpio_pin_t pin);

static inline void init_usart(LL_GPIO_InitTypeDef * p);

typedef struct exti_handler_t {

} exti_handler_t;

static gpio_interface_t interface = {
        .set_pin = set_pin,
        .reset_pin = reset_pin,
        .read_port = read_port,
        .init_pin = init_pin,
        .attach_cb = attach_cb,
        .read_pin = read_pin,
        .write_port = write_port,
        .toggle = toggle,
};

#define MAX_EXTI_HANDLERS 1

static struct
{
    gpio_t base;
    LL_GPIO_InitTypeDef init;
    exti_handler_t handlers[1];

} self = {0};


GPIO
stm32_gpio_create()
{
    self.base.vtable = &interface;
    init_usart(&self.init);
    return &self.base;
}

#define INIT_NORMAL_PIN(port, pin)          \
    self.init.Pin  = (pin);                 \
    self.init.Mode = LL_GPIO_MODE_OUTPUT;   \
    self.init.Pull = LL_GPIO_PULL_NO;       \
    LL_GPIO_Init((port), &self.init)

#define INIT_EXTI_PIN(port, pin)            \
    self.init.Pin  = (pin);                 \
    self.init.Mode = LL_GPIO_MODE_INPUT;    \
    self.init.Pull = LL_GPIO_PULL_NO;       \
    LL_GPIO_Init((port), &self.init)

#define INIT_ADC_PIN(port, pin) \
    self.init.Pin  = (pin);                 \
    self.init.Mode = LL_GPIO_MODE_ANALOG;   \
    self.init.Pull = LL_GPIO_PULL_NO;       \
    LL_GPIO_Init((port), &self.init)

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

#if STM32_ENABLE_USART2_ONEWIRE
    p->Pin        = STM32_USART2_TX_PIN;
    p->Mode       = LL_GPIO_MODE_ALTERNATE;
    p->Speed      = LL_GPIO_SPEED_FREQ_LOW;
    p->OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    p->Pull       = LL_GPIO_PULL_UP;
    p->Alternate  = LL_GPIO_AF_1;
    LL_GPIO_Init(STM32_USART2_RX_PORT, p);

#else
    p->Pin        = STM32_USART2_RX_PIN;
    p->Mode       = LL_GPIO_MODE_ALTERNATE;
    p->Speed      = LL_GPIO_SPEED_FREQ_LOW;
    p->OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    p->Pull       = LL_GPIO_PULL_UP;
    p->Alternate  = LL_GPIO_AF_1;
    LL_GPIO_Init(STM32_USART2_RX_PORT, p);


    p->Pull       = LL_GPIO_PULL_NO;
    p->Pin = STM32_USART2_TX_PIN;
    LL_GPIO_Init(STM32_USART2_TX_PORT, p);
#endif


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
set_pin(gpio_port_t port, gpio_pin_t pin)
{
    LL_GPIO_SetOutputPin(port, pin);
}

static inline void
reset_pin(gpio_port_t port, gpio_pin_t pin)
{
    LL_GPIO_ResetOutputPin(port, pin);
}

static inline uint32_t
read_port(gpio_port_t port)
{
    return LL_GPIO_ReadInputPort(port);
}

static inline uint8_t
read_pin(gpio_port_t port, gpio_pin_t pin)
{
    return LL_GPIO_IsOutputPinSet(port, pin);
}

static inline void
write_port(gpio_port_t port, uint32_t value)
{
    LL_GPIO_WriteOutputPort(port, value);
}

static inline void
toggle(gpio_port_t port, gpio_pin_t pin)
{
    LL_GPIO_TogglePin(port, pin);
}

static inline void
init_pin(gpio_port_t port, gpio_pin_t pin, uint8_t pin_mode)
{
    switch (pin_mode) {
        case GPIO_PIN_MODE_NORMAL:
            INIT_NORMAL_PIN(port, pin);
            break;
        case GPIO_PIN_MODE_INTERRUPT:
            INIT_EXTI_PIN(port, pin);
            break;
        case GPIO_PIN_MODE_ANALOG:
            INIT_ADC_PIN(port, pin);
            break;
        default:
            break;
    }
}

static inline void
attach_cb(gpio_port_t port, gpio_pin_t pin, void (* cb)(), bool active_high)
{

}


/** @brief EXTI Line 0 and 1 interrupt handler */
__INTERRUPT
EXTI0_1_IRQHandler()
{
    if (LL_EXTI_IsActiveRisingFlag_0_31(LL_EXTI_LINE_0)) {

    }
}

/** @brief EXTI Line 2 and 3 interrupt handler */
__INTERRUPT
EXTI2_3_IRQHandler()
{

}

/** @brief EXTI Line 4 to 15 interrupt handler */
__INTERRUPT
EXTI4_15_IRQHandler()
{

}
