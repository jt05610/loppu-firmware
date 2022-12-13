/**
  ******************************************************************************
  * @file   stm32.c
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "../inc/stm32.h"
#include "stm32_uart.h"
#include "stm32_gpio.h"
#include "stm32_timer.h"
#include "stm32_clock.h"

#define TICK 16000000

static struct {
    adapter_t base;
    uint8_t rx_buffer[RX_BUFFER_SIZE];
}self = {0};

Adapter
stm32_adapter_create()
{
    clock_config(TICK);
    stm32_serial_params_t params = {
            .rx_buffer=self.rx_buffer,
            .tx_buffer=0,
            .rx_callback=0,
    };
    self.base.serial = stm32_serial_create(&params);
    stm32_timer_init_t timer_params = {
            TIM16,
            GeneralTimer
    };
    GEN_TIM(&timer_params).update_freq =
    self.base.timer = stm32_timer_create();
    self.base.gpio = 0;
    return &self.base;
}