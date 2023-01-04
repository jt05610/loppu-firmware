/**
  ******************************************************************************
  * @file   fake_device.h
  * @author jtaylor
  * @date   03 Jan 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef FAKEDEVICE_FAKEDEVICE_H
#define FAKEDEVICE_FAKEDEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup FakeDevice
 * @brief 
 * @{
 */

#include "peripherals.h"
#include "device.h"

/**
 * @brief Instantiates FAKEDEVICE
 * @param hal device-specific hardware abstraction layer. @see Peripherals
 * @param uart_inst Serial instance if needed by target mcu. @see Serial
 * @param tim_inst Timer instance if needed by target mcu. @see Timer
 */
Device fake_device_create(Peripherals hal, void * uart_inst, void * tim_inst);

/**
 * @brief Forever loop to run device.
 * @param device Device which has been instantiated.
 */
_Noreturn void fake_device_run(Device device);

/** @} */

#ifdef __cplusplus
}
#endif

#endif //FAKEDEVICE_FAKEDEVICE_H
