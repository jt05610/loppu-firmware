/**
  ******************************************************************************
  * @file   stm32.h
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

#ifndef INJECTOR_STM32_H
#define INJECTOR_STM32_H

#include "../../adapter/inc/adapter.h"
#include <sys/cdefs.h>

_Noreturn void Error_Handler(void);

#define __INTERRUPT __attribute__((unused)) void

Adapter stm32_adapter_create();

#endif //INJECTOR_STM32_H
