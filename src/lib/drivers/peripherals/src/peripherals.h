/**
  ******************************************************************************
  * @file   peripherals.h
  * @author Jonathan Taylor
  * @date   12/12/22
  * @brief  Peripherals header file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_PERIPHERALS_H
#define INJECTOR_PERIPHERALS_H

#include "serial.h"
#include "gpio.h"
#include "timer.h"

/** @addtogroup Drivers
 *  @{
 */

/**
 * @defgroup Peripherals
 * @brief General collection of hardware abstraction layer libraries.
 * @{
 */

/**
 * @brief Pointer to @ref peripherals_t.
 */
typedef struct peripherals_t * Peripherals;

/**
 * @brief Container of abstract hardware implementations.
 */
typedef struct peripherals_t {
    GPIO gpio;              /**< @brief Implemented @ref gpio_t instance. */
    Serial serial;          /**< @brief Implemented @ref serial_t instance. */
    Timer timer;            /**< @brief Implemented @ref timer_t instance. */
} peripherals_t;

/** @} */

/** @} */

#endif //INJECTOR_PERIPHERALS_H
