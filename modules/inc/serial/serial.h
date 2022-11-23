/**
  ******************************************************************************
  * @file   serial.h
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

#ifndef MICROFLUIDICSYSTEM_SERIAL_H
#define MICROFLUIDICSYSTEM_SERIAL_H

#include "project_types.h"

typedef struct serial_t           * Serial;
typedef struct serial_interface_t * SerialInterface;
typedef struct serial_init_t      * SerialInit;
typedef struct comm_port_t        * CommPort;
typedef struct comm_port_list_t   * CommPortList;

typedef enum serial_opt_t
{
    SerialReadOnly,
    SerialReadWrite,
    SerialWriteOnly,

} serial_opt_t;

typedef struct serial_init_t
{
    const char * port;
    uint32_t baud;
    uint8_t * rx_buffer;
} serial_init_t;

typedef struct comm_port_t
{
    const char * name;
    const char * device;
} comm_port_t;

typedef struct comm_port_list_t
{
    CommPort ports[255];
    uint8_t  n_ports;
} comm_port_list_t;

Serial serial_create(SerialInit params);

void serial_destroy(Serial base);

bool serial_open(Serial base);

bool serial_close(Serial base);

bool serial_write(Serial base, sized_array_t * data);

bool serial_read(Serial base, sized_array_t * dest);

uint32_t serial_get_baud(Serial base);

CommPortList serial_list_ports(Serial base);

void serial_set_options(Serial base, serial_opt_t option);

#include ".private/serial_private.h"

#endif //MICROFLUIDICSYSTEM_SERIAL_H
