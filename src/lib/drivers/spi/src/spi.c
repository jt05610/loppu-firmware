/**
  ******************************************************************************
  * @file   spi.c
  * @author Jonathan Taylor
  * @date   22 Mar 2023
  * @brief  SPI source file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "spi.h"


void
spi_open(SPI base, void * instance)
{
    if (base && base->vtable && base->vtable->open) {
        base->vtable->open(instance);
    }
}

void
spi_close(SPI base, void * instance)
{
    if (base && base->vtable && base->vtable->close) {
        base->vtable->close(instance);
    }
}

uint16_t
spi_read(SPI base, void * instance, uint8_t * dest)
{
    uint16_t ret = 0;
    if (base && base->vtable && base->vtable->read) {
        ret = base->vtable->read(instance, dest);
    }
    return ret;
}

uint16_t
spi_write(SPI base, void * instance, uint8_t * data, uint16_t size)
{
    uint16_t ret = 0;
    if (base && base->vtable && base->vtable->write) {
        ret = base->vtable->write(instance, data, size);
    }
    return ret;
}

void
spi_transact(SPI base, void * instance, uint8_t * r, uint8_t * w, uint16_t size)
{
    if (base && base->vtable && base->vtable->transact) {
        base->vtable->transact(instance, r, w, size);
    }
}

