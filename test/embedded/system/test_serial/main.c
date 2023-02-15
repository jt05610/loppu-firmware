/**
  ******************************************************************************
  * @file   main.c
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  ADC embedded system test runner.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "adapters/stm32/g031xx_adapter.h"
#include "serial.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_usart.h"
#include "unity_internals.h"
#include "test_serial.h"

static Peripherals hal;

static uint8_t result[10];

int main()
{
    uint16_t size;
    hal = bootstrap(stm32_dependency_injection, 0);
    serial_open(hal->serial, USART1);
    serial_open(hal->serial, USART2);
    UNITY_BEGIN();
    RUN_TEST(test_write);
    UNITY_END();
}

static uint8_t msg[8] = {0x05, 0x00, 0x02, 0x8F};

void
test_write()
{
    uint8_t expected[8] = {0x05, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 'L'};
    serial_read_write(hal->serial, USART2, msg, 4, 8);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(expected, msg, 8);
}

void test_close();
void test_read();
void test_flush();

void test_available();
void test_setTimeout();

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
