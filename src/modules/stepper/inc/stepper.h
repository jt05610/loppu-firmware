/**
  ******************************************************************************
  * @file   stepper.h
  * @author Jonathan Taylor
  * @date   7/11/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_STEPPER_H
#define DRIVERS_STEPPER_H

#include "gpio.h"
#include <stdbool.h>

/**
 * @defgroup Stepper
 * @brief Abstraction layer for stepper motor drivers
 * @{
 */

typedef struct stepper_t *Stepper;

#define STEPPER_DIR_CW   0x00
#define STEPPER_DIR_CCW  0x01
#define STEPPER_DIR_SAME 0xFF

typedef enum microstep_t {
    MS_FULL,
    MS_2,
    MS_4,
    MS_8,
    MS_16,
    MS_32,
    MS_64,
    MS_128,
    MS_256
} microstep_t;

/**
 * @brief Gets direction of stepper motor
 * @param base Stepper instance
 * @return direction that stepper is
 */
uint8_t stepper_get_dir(Stepper base);

/**
 * @brief Sets direction of stepper motor
 * @param base Stepper instance
 * @param dir Direction to set stepper to.
 */
void stepper_set_dir(Stepper base, uint8_t dir);

/**
 * @brief Gets velocity of stepper motor
int32_t  * @param base Stepper instance
 * @return Stepper velocity in µsteps / s.
 */
int32_t stepper_get_velocity(Stepper base);

/**
 * @brief Sets velocity of stepper motor
 * @param base Stepper instance
 * @param value Desired stepper velocity in µsteps / s.
 */
void stepper_set_velocity(Stepper base, int32_t value);

/**
 * Gets stepper microstep
 * @param base Stepper instance
 * @return stepper microstep value
 */
microstep_t stepper_get_microstep(Stepper base);

/**
 * Sets stepper microstep
 * @param base Stepper instance
 * @param microstep desired microstep
 */
void stepper_set_microstep(Stepper base, microstep_t microstep);

/**
 * Enables or disables stepper
 * @param base Stepper instance
 * @param enabled true to enable, false to disable
 */
void stepper_set_enabled(Stepper base, bool enabled);

/**
 * Gets whether the stepper is enabled or disabled
 * @param base Stepper instance
 * @return true if enabled, false if disabled
 */
bool stepper_get_enabled(Stepper base);

/**
 * Periodic job to call for stepper
 * @param base Stepper instance
 */
void stepper_periodic_job(Stepper base);

#include "stepper_private.h"

/** @} */

#endif //DRIVERS_STEPPER_H

