/**
  ******************************************************************************
  * @file   serial.c
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "serial.h"

void
serial_open(Serial base, void * instance)
{
    if (base && base->vtable && base->vtable->open)
        base->vtable->open(instance);
}

void
serial_close(Serial base, void * instance)
{
    if (base && base->vtable && base->vtable->close)
        base->vtable->close(instance);
}

uint16_t
serial_read(Serial base, void * instance, uint8_t * dest)
{
    uint16_t ret = 0;
    if (base && base->vtable && base->vtable->read)
        ret = base->vtable->read(instance, dest);
    return ret;
}

void
serial_write(Serial base, void * instance, uint8_t * data, uint16_t size)
{
    if (base && base->vtable && base->vtable->write)
        base->vtable->write(instance, data, size);
}

void
serial_putchar(Serial base, void * instance, uint8_t a)
{
    if (base && base->vtable && base->vtable->putchar)
        base->vtable->putchar(instance, a);
}

void
serial_attach_buffer(Serial base, uint8_t * buffer, uint16_t size)
{
    base->rx_buffer = buffer;
    base->buffer_size = size;
    base->buffer_position = 0;
}
