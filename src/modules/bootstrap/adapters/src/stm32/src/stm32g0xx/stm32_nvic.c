/**
  ******************************************************************************
  * @file   stm32_nvic.c
  * @author Jonathan Taylor
  * @date   12/17/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32g031xx.h"
#include "stm32_nvic.h"
#include "default/nvic_config.h"

#define NVIC_INIT(i, p) NVIC_SetPriority((i), (p)); NVIC_EnableIRQ((i))

void stm32_nvic_init()
{

}
