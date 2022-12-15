/**
  ******************************************************************************
  * @file   stm32g0xx_interface.c
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  STM32G0xx interface source.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32g0xx_interface.h"
#include "stm32g0xx/stm32_timer.h"


peripherals_t self = {0};

Peripherals
stm32_dependency_injection(void * params)
{
   stm32_init_t * p = (stm32_init_t *)params;

   /*
    * Timer init
    */
   stm32_timer_init_t timer_params = {

   };
   self.timer = stm32_timer_create(&timer_params);

   return &self;
}
