/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef __USART_H__
#define __USART_H__

#include "timer.h"
#include "serial.h"
#include "stm32_gpio.h"

#define RX_DMA DMA1
#define RX_CHANNEL LL_DMA_CHANNEL_1
#define RX_PIN LL_GPIO_PIN_7
#define RX_PORT GPIOB

#define TX_DMA DMA1
#define TX_CHANNEL LL_DMA_CHANNEL_2
#define TX_PIN LL_GPIO_PIN_6
#define TX_PORT GPIOB

#define RE_PIN LL_GPIO_PIN_11
#define DE_PIN LL_GPIO_PIN_12
#define DE_PORT GPIOA

typedef struct stm32_serial_params_t
{
    volatile uint8_t * rx_buffer;
    volatile uint8_t * tx_buffer;
    uint16_t (*rx_callback)(uint16_t size);
} stm32_serial_params_t;

Serial stm32_serial_create(stm32_serial_params_t * params);


#endif /* __USART_H__ */

