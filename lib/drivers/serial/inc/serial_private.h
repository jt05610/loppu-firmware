/**
  ******************************************************************************
  * @file   serial_private.h
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

#ifndef MICROFLUIDICSYSTEM_SERIAL_PRIVATE_H
#define MICROFLUIDICSYSTEM_SERIAL_PRIVATE_H

#include "serial.h"

#ifndef MICROFLUIDICSYSTEM_SERIAL_H
#include "serial.h"
#endif

typedef struct serial_interface_t
{
    void (* open)(Serial base);

    void (* close)(Serial base);

    uint16_t (* read)(Serial base, uint8_t * dest);

    void (* write)(Serial base, uint8_t * data, uint16_t size);

} serial_interface_t;

typedef struct serial_t
{
    uint8_t * rx_buffer;
    uint16_t buffer_size;
    uint16_t buffer_position;
    SerialInterface vtable;
} serial_t;

#endif //MICROFLUIDICSYSTEM_SERIAL_PRIVATE_H
