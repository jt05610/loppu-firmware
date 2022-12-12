/**
  ******************************************************************************
  * @file   posix_timer.c
  * @author Jonathan Taylor
  * @date   7/29/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef STM32G031xx
#ifndef WIN32

#include "posix_timer.h"
#include <sys/time.h>

static struct
{
    Timer          base;
    struct timeval spec;
} self = {0};

#define UPDATE gettimeofday(&self.spec, NULL)

static inline time_amount_t micros();

static inline time_amount_t millis();

static inline void delay(time_amount_t ms);

static inline void delay_micros(time_amount_t us);

static timer_interface_t interface = {
        .delay=delay,
        .delay_micros=delay_micros,
        .millis=millis,
        .micros=micros
};

void
posix_timer_create(Timer time)
{
    self.base    = time;
    time->vtable = &interface;
}

static inline time_amount_t
micros()
{
    UPDATE;
    return ((time_amount_t) self.spec.tv_sec * 1000000) + self.spec.tv_usec;
}

static inline time_amount_t millis()
{
    UPDATE;
    return ((time_amount_t) self.spec.tv_sec * 1000)
           + (self.spec.tv_usec / 1000);
}

static inline void delay(time_amount_t ms)
{
    time_amount_t start = millis();
    while (millis() - start < ms);
}

static inline void delay_micros(time_amount_t us)
{

    time_amount_t start = micros();
    while (micros() - start < us);
}

struct timeval *
posix_time_stamp()
{
    UPDATE;
    return &self.spec;
}

#endif
#endif