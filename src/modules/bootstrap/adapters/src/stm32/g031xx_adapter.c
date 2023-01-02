/**
  ******************************************************************************
  * @file   stm32g0xx_interface.c
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  STM32G0xx interface source.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "peripherals.h"
#include "default.h"

#include "stm32g0xx/stm32_rcc.h"
#include "stm32g0xx/stm32_adc.h"
#include "stm32g0xx/stm32_serial.h"
#include "stm32g0xx/stm32_timer.h"
#include "stm32g0xx/stm32_gpio.h"
#include "stm32g0xx/stm32_dma.h"
#include "stm32g0xx/stm32_nvic.h"

static peripherals_t self = {0};

static inline void
adc_config()
{
#if STM32_ENABLE_ADC
    self.analog = stm32_adc_create();
#endif
}

static inline void
dma_config()
{
#if STM32_ENABLE_DMA
    stm32_dma_mem_addr_t addr = {
#if STM32_ADC_ENABLE_DMA
            .adc=(uint32_t) stm32_adc_get_buffer(),
#endif
#if STM32_ENABLE_USART1_RX_DMA
            .usart1_rx=stm32_get_usart1_rx_circ_buffer(),
             .usart1_rx_buffer=stm32_get_usart1_rx_circ_buffer(),
#endif
#if STM32_ENABLE_USART1_TX_DMA
            .usart1_tx=0,
#endif
#if STM32_ENABLE_USART2_RX_DMA
            .usart2_rx=(uint32_t) stm32_get_usart2_rx_buffer(),
#endif
#if STM32_ENABLE_USART2_TX_DMA
            .usart2_tx=(uint32_t) stm32_get_usart2_tx_buffer(),
#endif
    };
    stm32_dma_create(&addr);
#endif
}

static inline void
gpio_config()
{
#if STM32_ENABLE_GPIO
    self.gpio = stm32_gpio_create();
#endif
}

static inline void
serial_config()
{
#if STM32_ENABLE_SERIAL
    self.serial = stm32_serial_create();
#endif
}

static inline void
timer_config()
{
#if STM32_ENABLE_TIMER
    self.timer = stm32_timer_create();
#endif
}

Peripherals
stm32_dependency_injection()
{
    stm32_rcc_config();
    adc_config();
    gpio_config();
    serial_config();
    dma_config();
    timer_config();
    stm32_nvic_config();
    return &self;
}