/**
  ******************************************************************************
  * @file   stm32_adc.h
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_STM32_ADC_H
#define INJECTOR_STM32_ADC_H

#include "analog.h"

#define ADC_BUFFER_SIZE 100

Analog stm32_adc_create();

static uint16_t adc_buffer[ADC_BUFFER_SIZE];

#endif //INJECTOR_STM32_ADC_H
