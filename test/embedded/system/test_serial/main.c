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

static Peripherals hal;

static uint8_t result[10];

int main()
{
    uint16_t size;
    hal = bootstrap(stm32_dependency_injection, 0);
    serial_open(hal->serial, USART1);
    while (1) {
        if (serial_available(hal->serial, USART1)) {
            size = serial_read(hal->serial, USART1, result);
            if (size) {
                serial_write(hal->serial, USART1, result, size);
                serial_clear(hal->serial, USART1);
            }
        }
    }
}