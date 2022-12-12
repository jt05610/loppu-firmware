/**
  ******************************************************************************
  * @file   timer_math.h
  * @author Jonathan Taylor
  * @date   7/21/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_TIMER_MATH_H
#define DRIVERS_TIMER_MATH_H

#include "../../modbus/inc/public/modbus/project_types.h"

static inline uint16_t
calculate_prescaler(uint32_t input_clock, uint32_t out_clock)
{
    uint16_t ret = 0;
    if (input_clock >= out_clock)
        ret = ((input_clock + out_clock / 2U) / out_clock) - 1;
    return ret;
}

static inline uint32_t
calculate_period(uint32_t input_clock, uint32_t prescaler, uint32_t signal_freq)
{
    uint32_t ret = 0;
    if (input_clock / (prescaler + 1) >= signal_freq)
        ret = (uint32_t) (input_clock / (signal_freq * (prescaler + 1))) - 1;
    return ret;
}

static inline uint32_t
calculate_pulse(uint32_t period, uint32_t duty_cycle)
{
    return (period * duty_cycle) / 100;
}

#endif //DRIVERS_TIMER_MATH_H
