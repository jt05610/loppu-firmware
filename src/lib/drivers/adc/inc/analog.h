/**
  ******************************************************************************
  * @file   analog.h
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_ANALOG_H
#define INJECTOR_ANALOG_H

/**
 * @addtogroup Peripherals
 * @{
 */

/**
 * @defgroup ADC
 * @brief Analog-to-digital converter abstraction layer
 * @{
 */
#include <stdint.h>

#define MAX_WATCHDOGS 3     /**< @brief Max ADX watchdogs */

/**< @brief: Pointer to ADC instance */
typedef struct adc_base_t * Analog;

/** @brief: Pointer to ADC Watchdog instance */
typedef struct adc_watchdog_t * ADCWatchdog;

/** @brief: Pointer to ADC interface instance */
typedef struct adc_interface_t * ADCInterface;

/**
 * @brief Interface to start ADC conversion.
 * @param base ADC instance
 * @param data Any data needed to pass to start adc on target mcu.
 */
void adc_start(Analog base, void * data);

/**
 * @brief Interface to start ADC conversion.
 * @param base ADC instance
 * @param data Any data needed to pass to start adc on target mcu.
 */
void adc_stop(Analog base, void * data);

/**
 * @brief Averages all values stored in data buffer
 * @param base ADC instance
 * @return Average of all values in buffer
 */
uint16_t adc_average(Analog base);

/**
 * @brief Add watchdog to trigger a callback if read value is above or below
 *        passed values in pointer to @ref adc_watchdog_t.
 * @param base ADC instance.
 * @param data Any data needed to pass for watchdog instantiation.
 * @param watchdog Watchdog instance.
 */
void adc_add_watchdog(Analog base, uint8_t data, ADCWatchdog watchdog);

#include "analog_private.h"

/** @} */

/** @} */

#endif //INJECTOR_ANALOG_H
