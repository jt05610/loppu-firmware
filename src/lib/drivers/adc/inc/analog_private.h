/**
  ******************************************************************************
  * @file   analog_private.h
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  Analog driver private header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_ANALOG_PRIVATE_H
#define DRIVERS_ANALOG_PRIVATE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ADC
 * @{
 */

#include <stdint.h>

/** @brief Data structure for adc watchdog initialization */
typedef struct adc_watchdog_t
{
    /** @brief any data needed to initialize or use callback */
    uint8_t data;

    /** @brief Trigger cb if reading is greater than this value */
    uint16_t max_value;

    /** @brief Trigger cb if reading is less than this value */
    uint16_t min_value;

    /** @brief Function to run if either threshold is crossed */
    void (* cb)();

} adc_watchdog_t;

/** @brief Device specific adc interface functions. */
typedef struct adc_interface_t
{

    /**
     * @brief Start ADC conversion
     */
    void (* start)();

    /**
    * @brief Stop ADC conversion
    */
    void (* stop)();

    /**
     * @brief Adds watchdog to adc instance.
     * @param watchdog Implemented @ref adc_watchdog_t
     */
    void (* add_watchdog)(ADCWatchdog watchdog);

} adc_interface_t;

/** @brief ADC base data structure */
typedef struct adc_base_t
{
    uint16_t n_samples;               /**< @brief Number of samples to store */
    volatile uint16_t * buffer;       /**< @brief Location of samples */
    adc_interface_t   * vtable;       /**< @brief MCU specific functions */
} adc_base_t;
/** @} */

#ifdef __cplusplus
}
#endif

#endif //DRIVERS_ANALOG_PRIVATE_H
