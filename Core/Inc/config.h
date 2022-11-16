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

#define EXTI_0_1_BIT_MASK 0x03

#define BLINKY_UPDATE_FREQ 1000 // Hz

#define BLINKY_DEFAULT_DELAY_MS 1000

#define BLINKY_DEFAULT_DELAY_US (1000 * BLINKY_DEFAULT_DELAY_MS)
#endif //INJECTOR_CONFIG_H
