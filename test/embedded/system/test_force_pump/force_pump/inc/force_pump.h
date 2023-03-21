/**
  ******************************************************************************
  * @file   force_pump.h
  * @author jtaylor
  * @date   21 Mar 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef FORCE_PUMP_FORCE_PUMP_H
#define FORCE_PUMP_FORCE_PUMP_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup force_pump
 * @brief 
 * @{
 */

#include "peripherals.h"
#include "device.h"

/**
 * @brief Instantiates FORCE_PUMP
 * @param hal device-specific hardware abstraction layer. @see Peripherals
 * @param uart_inst Serial instance if needed by target mcu. @see Serial
 * @param tim_inst Timer instance if needed by target mcu. @see Timer
 */
Device force_pump_create(Peripherals hal, void * uart_inst, void * tim_inst);

/**
 * @brief Forever loop to run device.
 * @param device Device which has been instantiated.
 */
_Noreturn void force_pump_run(Device device);

/** @} */

#ifdef __cplusplus
}
#endif

#endif //FORCE_PUMP_FORCE_PUMP_H
