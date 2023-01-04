/**
  ******************************************************************************
  * @file   pressure_sensor.h
  * @author Jonathan Taylor
  * @date   04 Jan 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef PRESSURESENSOR_PRESSURESENSOR_H
#define PRESSURESENSOR_PRESSURESENSOR_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup PressureSensor
 * @brief 
 * @{
 */

#include "peripherals.h"
#include "device.h"

/**
 * @brief Instantiates PRESSURESENSOR
 * @param hal device-specific hardware abstraction layer. @see Peripherals
 * @param uart_inst Serial instance if needed by target mcu. @see Serial
 * @param tim_inst Timer instance if needed by target mcu. @see Timer
 */
Device pressure_sensor_create(Peripherals hal, void * uart_inst, void * tim_inst);

/**
 * @brief Forever loop to run device.
 * @param device Device which has been instantiated.
 */
_Noreturn void pressure_sensor_run(Device device);

/** @} */

#ifdef __cplusplus
}
#endif

#endif //PRESSURESENSOR_PRESSURESENSOR_H
