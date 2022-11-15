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

#include "serial/serial.h"

typedef struct serial_interface_t
{
    bool (* open)(void);

    bool (* close)(void);

    bool (* read)(sized_array_t * dest);

    bool (* write)(const sized_array_t * data);

    CommPortList (* list_ports)(void);

    void (* set_options)(serial_opt_t options);

} serial_interface_t;

typedef struct serial_t
{
    SerialInterface vtable;
    uint32_t        baud;
} serial_t;

#endif //MICROFLUIDICSYSTEM_SERIAL_PRIVATE_H
