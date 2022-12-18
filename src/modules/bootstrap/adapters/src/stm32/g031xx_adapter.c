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

#if STM32_ENABLE_ADC

#include "stm32g0xx/stm32_adc.h"

#endif

#if !STM32_ENABLE_SERIAL

#include "stm32g0xx/stm32_serial.h"

#endif

#if STM32_ENABLE_TIMER

#include "stm32g0xx/stm32_timer.h"

#endif

#if STM32_ENABLE_GPIO

#include "stm32g0xx/stm32_gpio.h"

#endif

#if STM32_ENABLE_DMA

#include "stm32g0xx/stm32_dma.h"

#endif
peripherals_t self = {0};

Peripherals
stm32_dependency_injection(void * params)
{
    (void) params;
    stm32_rcc_config();

#if STM32_ENABLE_DMA
    stm32_dma_mem_addr_t dma_params = {
#if STM32_USART1_RX_ENABLE_DMA
            .usart1_rx=0,
#endif
            .usart2_rx=0,
#if STM32_USART1_RX_ENABLE_DMA
            .adc=(uint32_t) self.analog->buffer
#endif
#if STM32_USART1_RX_ENABLE_DMA
#endif
    };
    stm32_dma_create(&dma_params);
#endif

#if STM32_ENABLE_GPIO
    self.gpio = stm32_gpio_create();
#endif

#if STM32_ENABLE_ADC
    self.analog = stm32_adc_create();
#endif

#if STM32_ENABLE_TIMER
    self.timer = stm32_timer_create();
#endif

#if !STM32_ENABLE_SERIAL
    self.serial = stm32_serial_create();
#endif

    return &self;
}
