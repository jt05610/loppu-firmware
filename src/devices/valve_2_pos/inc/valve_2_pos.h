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

typedef struct valve_2_pos_t {
    Peripherals hal;
    device_t base;
    primary_table_t tables[4];
    gpio_pin_t pin;
    void *uart_inst;
    void *tim_inst;
    void *gpio_inst;
} valve_2_pos_t;

/**
 * @brief Instantiates valve_2_pos device.
 * @param params Parameters to configure device.
 */
Device valve_2_pos_create(valve_2_pos_t *params);

/**
 * @brief Forever loop to run device.
 * @param device Device which has been instantiated.
 */
void valve_2_pos_run(Device device);

/** @} */

#ifdef __cplusplus
}
#endif

#endif //FORCE_PUMP_FORCE_PUMP_H
