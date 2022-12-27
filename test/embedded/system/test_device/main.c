/**
  ******************************************************************************
  * @file   main.c
  * @author Jonathan Taylor
  * @date   12/26/22
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
#include "device.h"
#include "unity.h"
#include "stm32g031xx.h"

Device self;

void setUp()
{

}

void tearDown()
{

}

int main()
{
    UNITY_BEGIN();
    UNITY_END();
    while (1) {}
}

uint8_t
unity_output_char(char a)
{
    return serial_putchar(self->hal->serial, USART1, a);
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

}



