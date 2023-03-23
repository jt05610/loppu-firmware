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
#include "analog.h"
#include "spi.h"

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
typedef struct peripherals_t
{
    GPIO   gpio;          /**< @brief Implemented gpio instance. */
    Serial serial;        /**< @brief Implemented serial instance. */
    Timer  timer;         /**< @brief Implemented timer instance. */
    Analog analog;        /**< @brief Implemented analog instance. */
    SPI    spi;        /**< @brief Implemented analog instance. */

} peripherals_t;

/** @} */

/** @} */

#endif //INJECTOR_PERIPHERALS_H
