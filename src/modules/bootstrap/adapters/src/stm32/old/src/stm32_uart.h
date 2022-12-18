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



typedef struct stm32_serial_params_t
{

} stm32_serial_params_t;

Serial stm32_serial_create(stm32_serial_params_t * params);


#endif /* __USART_H__ */

