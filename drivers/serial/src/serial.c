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

#include "../inc/serial.h"

bool
serial_open(Serial base)
{
    bool ret = false;
    if (base && base->vtable && base->vtable->open)
        ret = base->vtable->open();
    return ret;
}

bool
serial_close(Serial base)
{
    bool ret = false;
    if (base && base->vtable && base->vtable->open)
        ret = base->vtable->close();
    return ret;
}

bool
serial_read(Serial base, sized_array_t * dest)
{
    bool ret = false;
    if (base && base->vtable && base->vtable->read)
        ret = base->vtable->read(dest);
    return ret;
}

bool
serial_write(Serial base, sized_array_t * data)
{
    bool ret = false;
    if (base && base->vtable && base->vtable->write)
        ret = base->vtable->write(data);
    return ret;
}

uint32_t
serial_get_baud(Serial base)
{
    return base->baud;
}

CommPortList
serial_list_ports(Serial base)
{
    if (base && base->vtable && base->vtable->list_ports)
        return base->vtable->list_ports();
    return 0;
}

void
serial_set_options(Serial base, serial_opt_t options)
{
    if (base && base->vtable && base->vtable->set_options)
        base->vtable->set_options(options);
}
