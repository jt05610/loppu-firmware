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
#include "stdlib.h"

static Peripherals hal;

static uint8_t result[10];

int main()
{
    uint16_t size;
    hal = bootstrap(stm32_dependency_injection, 0);
    serial_open(hal->serial, USART1);
    serial_open(hal->serial, USART2);
    UNITY_BEGIN();
    RUN_TEST(test_read);
    //RUN_TEST(test_write);
    UNITY_END();
}


bool done;
uint16_t       n;
uint8_t * dest;
uint16_t len;
void
rto_cb()
{
    uint16_t a = serial_available(hal->serial, USART1);
    TEST_ASSERT_EQUAL(len, a);
    for (uint16_t i = 0; i < a; i ++ ) {
        dest[i] = circ_buf_pop(hal->serial->serial_buffer);
    }
    serial_clear(hal->serial, USART1);
    done = true;
}

void test_read()
{
    serial_register_rx_callback(hal->serial, USART1, rto_cb);
    srand(42);
    for (uint16_t i = 0; i < 100; i++) {
        len = 7;
        uint8_t * buffer = malloc(len * sizeof(uint8_t));
        dest = calloc(len, sizeof(uint8_t));
        done = false;
        serial_write(hal->serial, USART2, buffer, len);
        while (!done);
        for (uint16_t j = 0; j < len; j++) {
            TEST_ASSERT_EQUAL(buffer[j], dest[j]);
        }
        free(dest);
        free(buffer);
    }
}

void
test_write()
{
    uint8_t expected[8] = {0x05, 0xFF, 0x02, 0x00, 0x00, 0x00, 0x00, 'L'};
//serial_read_write(hal->serial, USART2, msg, 4, 8);
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
