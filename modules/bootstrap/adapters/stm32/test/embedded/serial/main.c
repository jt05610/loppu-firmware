/**
  ******************************************************************************
  * @file   runner.c
  * @author Jonathan Taylor
  * @date   12/13/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32g031xx.h"
#include "stm32g0xx/stm32_clock.h"
#include "test_serial.h"
#include "test_modbus.h"
#include "unity.h"

static Serial instance = {0};

void
setUp()
{

}

void
tearDown()
{

}


int
main()
{
    stm32_clock_config();
    instance = stm32_serial_create();
    set_serial_test_instance(instance);
    UnityBegin("");
    RUN_TEST(test_read);
    RUN_TEST(test_write);
    UnityEnd();
    while (1) {}
}

void
unity_output_start()
{
    serial_open(instance, (void*)USART1);
}

uint8_t
unity_output_char(char a)
{

    serial_putchar(instance, (void*)USART1, (uint8_t)a);
    return (uint8_t)a;
}

void
unity_output_flush()
{

}

void
unity_output_complete()
{
    serial_close(instance, USART1);
    while (1) {}
}
