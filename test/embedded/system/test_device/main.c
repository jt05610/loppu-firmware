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

#include "fake_device.h"
#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g031xx.h"

static Device self;

void setUp()
{

}

void tearDown()
{

}

void test_write()
{

}

static Peripherals hal;

int main()
{
    hal = bootstrap(stm32_dependency_injection, 0);
    self = fake_device_create(hal, USART1, TIM2);
    fake_device_run(self);
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



