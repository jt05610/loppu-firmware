/**
  ******************************************************************************
  * @file   analog.c
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  DESCRIPTION
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
    adc_stop(base, 0);
    result = buffer_sum(base) / base->n_samples;
    adc_start(base, 0);
    return result;
}

void
adc_start(Analog base, void * data)
{
    if (base && base->vtable && base->vtable->start)
        base->vtable->start(data);
}

void
adc_stop(Analog base, void * data)
{
    if (base && base->vtable && base->vtable->stop)
        base->vtable->stop(data);
}

void
adc_add_watchdog(Analog base, uint8_t data, ADCWatchdog watchdog)
{
    if (base && base->vtable && base->vtable->add_watchdog)
        base->vtable->add_watchdog(data, watchdog);
}
