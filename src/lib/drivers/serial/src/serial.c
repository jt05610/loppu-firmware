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

uint8_t
serial_putchar(Serial base, void * instance, char a)
{
    if (base && base->vtable && base->vtable->putchar)
        return base->vtable->putchar(instance, a);
    return 0;
}

uint16_t serial_available(Serial base, void * instance)
{
    if (base && base->vtable && base->vtable->available)
        return base->vtable->available(instance);
    return 0;
}

void serial_clear(Serial base, void * instance)
{
    if (base && base->vtable && base->vtable->clear)
        base->vtable->clear(instance);
}

void
serial_attach_buffer(Serial base, circ_buf_t * buffer)
{
    base->serial_buffer = buffer;
}

bool
serial_buffer_transfer(Serial base, circ_buf_t * src)
{
    return circ_buf_transfer(base->serial_buffer, src);
}
