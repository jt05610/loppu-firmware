/**
  ******************************************************************************
  * @file   tmc2209_eval.h
  * @author Jonathan Taylor
  * @date   14 Feb 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef TMC2209EVAL_TMC2209EVAL_H
#define TMC2209EVAL_TMC2209EVAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup TMC2209Eval
 * @brief 
 * @{
 */
#include "config.h"
#include "peripherals.h"
#include "device.h"
#include "stepper.h"

/**
 * @brief Instantiates TMC2209EVAL
 * @param hal device-specific hardware abstraction layer. @see Peripherals
 * @param uart_inst Serial instance if needed by target mcu. @see Serial
 * @param tim_inst Timer instance if needed by target mcu. @see Timer
 * @param stepper Stepper instance @see Stepper
 */
Device tmc2209_eval_create(Peripherals hal, void * uart_inst, void * tim_inst, Stepper stepper);

/**
 * @brief Forever loop to run device.
 * @param device Device which has been instantiated.
 */
_Noreturn void tmc2209_eval_run(Device device);

/** @} */

#ifdef __cplusplus
}
#endif

#endif //TMC2209EVAL_TMC2209EVAL_H
