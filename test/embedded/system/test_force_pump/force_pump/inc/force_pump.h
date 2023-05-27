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
#include "linear_axis.h"

typedef struct force_pump_init_t
{
    Peripherals hal;
    Axis axis;
    void * uart_inst;
    void * tim_inst;
    void * spi_inst;

} force_pump_init_t;

/**
 * @brief Instantiates FORCE_PUMP
 * @param hal device-specific hardware abstraction layer. @see Peripherals
 * @param Axis Linear axis instance
 * @param uart_inst Serial instance if needed by target mcu. @see Serial
 * @param tim_inst Timer instance if needed by target mcu. @see Timer
 */
Device force_pump_create(force_pump_init_t *params);

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
