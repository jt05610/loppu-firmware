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
    if (base && base->vtable && base->vtable->open) {
        base->vtable->open(instance);
    }
}

void
serial_close(Serial base, void * instance)
{
    if (base && base->vtable && base->vtable->close) {
        base->vtable->close(instance);
    }
}

uint16_t
serial_read(Serial base, void * instance, uint8_t * dest)
{
    uint16_t ret = 0;
    if (base && base->vtable && base->vtable->read) {
        ret = base->vtable->read(instance, dest);
    }
    return ret;
}

void
serial_write(Serial base, void * instance, uint8_t * data, uint16_t size)
{
    if (base && base->vtable && base->vtable->write) {
        base->vtable->write(instance, data, size);
    }
}

uint8_t
serial_putchar(Serial base, void * instance, char a)
{
    if (base && base->vtable && base->vtable->putchar) {
        return base->vtable->putchar(instance, a);
    }
    return 0;
}

uint16_t
serial_available(Serial base, void * instance)
{
    if (base && base->vtable && base->vtable->available) {
        return base->vtable->available(instance);
    }
    return 0;
}

void
serial_clear(Serial base, void * instance)
{
    if (base && base->vtable && base->vtable->clear) {
        base->vtable->clear(instance);
    }
}

void
serial_register_rx_callback(Serial base, void * instance, void (* cb)(void))
{
    if (base && base->vtable && base->vtable->reg_rx_cb) {
        base->vtable->reg_rx_cb(instance, cb);
    }
}

void
serial_read_write(
        Serial base, void * instance, uint8_t * data, uint16_t n_w,
        uint16_t n_r)
{
    if (base && base->vtable && base->vtable->read_write) {
        base->vtable->read_write(instance, data, n_w, n_r);
    }
}
