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

int main()
{
    hal = bootstrap(stm32_dependency_injection, 0);
    serial_open(hal->serial, USART1);
    while (1) {
        uint8_t l = serial_available(hal->serial, USART1);
        if (l) {
            for (uint8_t i = 0; i < l; i++) {
                serial_putchar(
                        hal->serial, USART1,
                        circ_buf_pop(hal->serial->serial_buffer));
            }
            serial_clear(hal->serial, USART1);
        }
    }
}