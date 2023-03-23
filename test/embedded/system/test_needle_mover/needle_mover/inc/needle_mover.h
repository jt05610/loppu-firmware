/**
  ******************************************************************************
  * @file   needle_mover.h
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
#ifndef NEEDLE_MOVER_NEEDLE_MOVER_H
#define NEEDLE_MOVER_NEEDLE_MOVER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup needle_mover
 * @brief 
 * @{
 */

#include "peripherals.h"
#include "device.h"
#include "linear_axis.h"

/**
 * @brief Instantiates NEEDLE_MOVER
 * @param hal device-specific hardware abstraction layer. @see Peripherals
 * @param uart_inst Serial instance if needed by target mcu. @see Serial
 * @param tim_inst Timer instance if needed by target mcu. @see Timer
 * @param Stepdir Stepdir instance
 * @param Axis Linear axis instance
 */
Device needle_mover_create(Peripherals hal, void * uart_inst, void * tim_inst, StepDir stepdir, Axis axis);

/**
 * @brief Forever loop to run device.
 * @param device Device which has been instantiated.
 */
_Noreturn void needle_mover_run(Device device);

/** @} */

#ifdef __cplusplus
}
#endif

#endif //NEEDLE_MOVER_NEEDLE_MOVER_H
