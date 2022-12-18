/**
  ******************************************************************************
  * @file   analog.c
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  Analog peripheral source.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "analog.h"

static inline uint32_t
buffer_sum(Analog base)
{
    uint32_t ret = 0;
    for (uint16_t i = 0; i < base->n_samples; i ++) {
        ret += base->buffer[i];
    }
    return ret;
}

uint16_t
adc_average(Analog base)
{
    uint16_t result;
    result = buffer_sum(base) / base->n_samples;
    return result;
}

void
adc_start(Analog base)
{
    if (base && base->vtable && base->vtable->start)
        base->vtable->start();
}

void
adc_stop(Analog base)
{
    if (base && base->vtable && base->vtable->stop)
        base->vtable->stop();
}

void
adc_add_watchdog(Analog base, ADCWatchdog watchdog)
{
    if (base && base->vtable && base->vtable->add_watchdog)
        base->vtable->add_watchdog(watchdog);
}
