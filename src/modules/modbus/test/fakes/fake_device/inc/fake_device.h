/**
  ******************************************************************************
  * @file   fake_device.h
  * @author jtaylor
  * @date   12 Dec 2022
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef FAKEDEVICE_FAKEDEVICE_H
#define FAKEDEVICE_FAKEDEVICE_H

#include "modbus.h"

#define FAKE_ADDRESS 0x01

typedef struct fake_device_t * FakeDevice;

typedef struct fake_device_t
{
    ServerApp server;
    uint16_t values[4];
} fake_device_t;

void fake_device_create(FakeDevice base);

void fake_device_set_value(FakeDevice base, uint8_t table, uint16_t value);

uint16_t fake_device_get_value(FakeDevice base, uint8_t table);

PrimaryTable fake_device_get_tables();

#endif //FAKEDEVICE_FAKEDEVICE_H
