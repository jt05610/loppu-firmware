/**
  ******************************************************************************
  * @file   analog_private.h
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

#ifndef INJECTOR_ANALOG_PRIVATE_H
#define INJECTOR_ANALOG_PRIVATE_H

#include "analog.h"

/**
 * @addtogroup ADC
 * @{
 */
#include <stdint.h>

/** @brief Data structure for adc watchdog initialization */
typedef struct adc_watchdog_t
{
    /** @brief Trigger cb if reading is greater than this value */
    uint16_t max_value;

    /** @brief Trigger cb if reading is less than this value */
    uint16_t min_value;

    /**< @brief Function to run if either threshold is crossed */
    void (* cb)();

} adc_watchdog_t;

/** @brief Device specific adc interface functions. */
typedef struct adc_interface_t {

    /**
     * @brief Start ADC conversion
     * @param privdata
     */
    void (*start)(void * privdata);

    /**
    * @brief Stop ADC conversion
    * @param privdata
    */
    void (*stop)(void * privdata);

    /**
     * @brief Adds watchdog to adc instance.
     * @param privdata Any data needed to pass for target mcu.
     * @param watchdog Implemented @ref adc_watchdog_t
     */
    void (*add_watchdog)(uint8_t privdata, ADCWatchdog watchdog);

} adc_interface_t;

/**< @brief: ADC base data structure */
typedef struct adc_base_t
{
    uint16_t n_samples;               /**< @brief Number of samples to store */
    volatile uint16_t * buffer;       /**< @brief Location of samples */
    ADCInterface vtable;              /**< @brief MCU specific functions */
} adc_base_t;

/** @} */

#endif //INJECTOR_ANALOG_PRIVATE_H
