/**
  ******************************************************************************
  * @file   config.h
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

#ifndef INJECTOR_CONFIG_H
#define INJECTOR_CONFIG_H

/* modbus */
#define MODBUS_ADDRESS 0x01

#ifdef STM32G031xx
/* pins */
#define FORWARD_PIN LL_GPIO_PIN_0
#define BACKWARD_PIN LL_GPIO_PIN_1
#define INJECT_PIN LL_GPIO_PIN_7
#define BUTTON_PORT GPIOA

#define DIR_PIN LL_GPIO_PIN_4
#define DIR_PORT GPIO_PORT_A

#define STEP_PIN LL_GPIO_PIN_5
#define STEP_PORT GPIO_PORT_A

#define ENABLE_PIN LL_GPIO_PIN_6
#define ENABLE_PORT GPIO_PORT_A

#endif
/* stepper */

#define DEFAULT_INCREMENT 10 // µm
#define DEFAULT_VELOCITY  20 // µm/s

#define STEPS_PER_MM (200 * 25)

#endif //INJECTOR_CONFIG_H
