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

static inline void init_usart(LL_GPIO_InitTypeDef * p);

static inline void init_timers(LL_GPIO_InitTypeDef * p);

static inline void init_adc(LL_GPIO_InitTypeDef * p);

static inline void init_gpio(LL_GPIO_InitTypeDef * p);

static struct {
    gpio_t base;
} self = {0};

GPIO
stm32_gpio_create()
{
    LL_GPIO_InitTypeDef init;
    init_gpio(&init);
    init_adc(&init);
    init_usart(&init);
    //init_timers(&init);
    return 0;
}

static inline void
init_gpio(LL_GPIO_InitTypeDef * p)
{

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


