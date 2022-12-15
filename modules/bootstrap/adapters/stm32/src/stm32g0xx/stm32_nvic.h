/**
  ******************************************************************************
  * @file   stm32_nvic.h
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

#ifndef INJECTOR_STM32_NVIC_H
#define INJECTOR_STM32_NVIC_H

#include <stdint.h>
#include "stm32g031xx.h"

static void
stm32_nvic_init(IRQn_Type irq, uint8_t priority)
{
    NVIC_SetPriority(irq, priority);
    NVIC_EnableIRQ(irq);
}

#endif //INJECTOR_STM32_NVIC_H
