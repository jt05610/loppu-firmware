/**
  ******************************************************************************
  * @file   config.h
  * @author Jonathan Taylor
  * @date   11/15/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_CONFIG_H
#define INJECTOR_CONFIG_H
#include "stm32g0xx_ll_gpio.h"

#define __INTERRUPT __attribute__((unused)) void

#define INJECTOR_TICK 16000000

#define DEFAULT_INCREMENT 0.01 // mm
#define DEFAULT_VELOCITY 0.02 // mm/s

#define FORWARD_PIN LL_GPIO_PIN_0
#define BACKWARD_PIN LL_GPIO_PIN_1
#define INJECT_PIN LL_GPIO_PIN_7
#define BUTTON_PORT GPIOA
#define STEPS_PER_MM (200 * 25)
#define DIR_PIN LL_GPIO_PIN_4
#define DIR_PORT GPIO_PORT_A

#define STEP_PIN LL_GPIO_PIN_5
#define STEP_PORT GPIO_PORT_A

#define ENABLE_PIN LL_GPIO_PIN_6
#define ENABLE_PORT GPIO_PORT_A
#define EXTI_0_1_BIT_MASK 0x03
#define BLINKY_UPDATE_FREQ 1000 // Hz

#define BLINKY_DEFAULT_DELAY_MS 1000

#define BLINKY_DEFAULT_DELAY_US (1000 * BLINKY_DEFAULT_DELAY_MS)
#endif //INJECTOR_CONFIG_H
