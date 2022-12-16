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

/**
 * @defgroup FakeDevice
 * @brief Device for testing modbus data model on stm32.
 * @{
 */

#include "modbus.h"
#include "peripherals.h"

/**
 * @brief Pointer to privately implemented fake device structure.
 */
typedef struct fake_device_t * FakeDevice;

/**
 * @brief Pointer to privately implemented fake device structure.
 * @param hal Peripherals data structure to run device on.
 * @param app_params Parameters for modbus app.
 * @return Pointer to fake device.
 */
FakeDevice fake_device_create(Peripherals hal, app_init_t * app_params);

/**
 * @brief Sets table value to given value.
 * @param base Fake device instance.
 * @param table Which table to write to.
 * @param value Value to set to table.
 */
void fake_device_set_value(FakeDevice base, uint8_t table, uint16_t value);

/**
 * @brief Gets value from fake device's table.
 * @param base Fake device instance.
 * @param table Table to retrieve value from.
 * @return Table's value.
 */
uint16_t
fake_device_get_value(FakeDevice base, uint8_t table);

/**
 * @brief Device entrypoint
 * @param device Instantiated fake device.
 */
void fake_device_run(FakeDevice device);

/** @} */

#endif //FAKEDEVICE_FAKEDEVICE_H
