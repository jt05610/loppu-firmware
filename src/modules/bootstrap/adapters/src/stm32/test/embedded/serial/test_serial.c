/**
  ******************************************************************************
  * @file   serial_test.c
  * @author Jonathan Taylor
  * @date   12/14/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "test_timer.h"
#include "stm32g031xx.h"
#include "stm32g0xx.h"
#include "unity.h"

static serial_base_t uart = {0};

void
set_serial_test_instance(Serial serial)
{
    uart.rx_buffer = serial->rx_buffer;
    uart.buffer_position = serial->buffer_position;
    uart.buffer_size = serial->buffer_size;
    uart.vtable = serial->vtable;
}

void
test_read()
{
    TEST_FAIL();
}


void
test_write()
{

}
