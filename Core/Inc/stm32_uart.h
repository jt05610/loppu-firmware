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

#include <timer/timer.h>
#include "serial/serial.h"
#include "stm32_gpio.h"

#define RX_BUFFER_SIZE 256
#define DMA_BUFF_SIZE 8
#define RX_TIMEOUT 39

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

void stm32_serial_create(Serial base, uint8_t * rx_buffer);

uint16_t stm32_serial_received_len();

void stm32_dma_transfer(uint16_t size);

typedef struct stm32_serial_pos_t
{
    volatile uint16_t old;
    volatile uint16_t new;
} stm32_serial_pos_t;

stm32_serial_pos_t * stm32_serial_current_pos();

#endif /* __USART_H__ */

