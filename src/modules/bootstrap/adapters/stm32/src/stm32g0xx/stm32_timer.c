/**
  ******************************************************************************
  * @file   timer.c
  * @author Jonathan Taylor
  * @date   12/13/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <stddef.h>
#include "stm32_timer.h"
#include "stm32g0xx_ll_tim.h"

static timer_base_t self = {0};

static inline void
start(void * timer_instance, uint32_t freq)
{

}

static inline void
stop(void * timer_instance)
{

}

static inline uint32_t
get_tick(void * timer_instance)
{
    return 0;
}

static timer_interface_t interface = {
        .start=start,
        .stop=stop,
        .get_tick=get_tick,
};


Timer
stm32_timer_create()
{
    self.vtable = &interface;
    return &self;
}

