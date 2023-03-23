/**
  ******************************************************************************
  * @file   main.c
  * @author Jonathan Taylor
  * @date   2/18/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
/**
  ******************************************************************************
  * @file   test_linear_axis.c
  * @author Jonathan Taylor
  * @date   2/18/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_gpio.h"
#include "bootstrap.h"
#include "unity.h"
#include "hx711.h"

static volatile Peripherals hal;

static HX711 device;

void
setUp()
{
    device = hx711_create(hal, LL_GPIO_PIN_1, LL_GPIO_PIN_6, GPIOA, TIM17);
}

void
tearDown()
{
}

void
testClockPulses()
{
    bool writeHigh = true;

    for (uint8_t i = 0; i < 20; i ++) {
        if (writeHigh) {
            gpio_set_pin(hal->gpio, GPIOB, LL_GPIO_PIN_0);
            writeHigh = false;

        } else {
            gpio_reset_pin(hal->gpio, GPIOB, LL_GPIO_PIN_0);
            writeHigh = true;
        }
        while (hx711_pulse_count(device) < 24);
        gpio_reset_pin(hal->gpio, GPIOB, LL_GPIO_PIN_0);
    }
    uint32_t v = hx711_read(device);
    TEST_ASSERT_NOT_EQUAL(v, 0x800000);
}

int
main()
{
    hal = bootstrap(stm32_dependency_injection, 0);
    gpio_init_pin(hal->gpio, GPIOA, LL_GPIO_PIN_1, GPIO_PIN_MODE_NORMAL);
    gpio_init_pin(hal->gpio, GPIOA, LL_GPIO_PIN_6, GPIO_PIN_MODE_INPUT);
    gpio_init_pin(hal->gpio, GPIOB, LL_GPIO_PIN_0, GPIO_PIN_MODE_NORMAL);
    gpio_reset_pin(hal->gpio, GPIOB, LL_GPIO_PIN_0);
    serial_open(hal->serial, USART1);
    RUN_TEST(testClockPulses);
    UNITY_END();
}


uint8_t
unity_output_char(char a)
{
    return serial_putchar(hal->serial, USART1, a);
}

void
unity_output_start()
{

}

void
unity_output_flush()
{

}

void
unity_output_complete()
{
    while (1);
}
