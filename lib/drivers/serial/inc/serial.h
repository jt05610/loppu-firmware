/**
  ******************************************************************************
  * @file   serial.h
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_SERIAL_H
#define DRIVERS_SERIAL_H

#include "stdbool.h"
#include <stdint.h>

/** @addtogroup Peripherals
 *  @{
 */

/**
 * @defgroup Serial
 * @brief Serial abstraction library.
 * @details To implement a serial library for a given mcu, a serial_interface_t
 *          must be implemented with definitions for the given function
 *          prototypes.
 * @{
 */

/**
 * @brief Pointer to @ref serial_base_t.
 */
typedef struct serial_base_t      * Serial;

/**
 * @brief Pointer to @ref serial_interface_t.
 */
typedef struct serial_interface_t * SerialInterface;

/**
 * @brief Opens serial device
 * @param base Serial instance
 * @param instance Serial instance if needed by target.
 */
void serial_open(Serial base, void * instance);

/**
 * @brief Closes serial device
 * @param base Serial instance
 * @param instance Serial instance if needed by target.
 */
void serial_close(Serial base, void * instance);

/**
 * @brief Read data from serial port
 * @param base Serial instance
 * @param instance Serial instance if needed by target.
 * @param dest buffer to read data into
 * @return number of read bytes
 */
uint16_t serial_read(Serial base, void * instance, uint8_t * dest);

/**
 * @brief Writes data to serial port
 * @param base Serial instance
 * @param instance Serial instance if needed by target.
 * @param data data to write
 * @param size number of bytes to write
 */
void serial_write(Serial base, void * instance, uint8_t * data, uint16_t size);

/**
 * @brief Writes single byte to serial port
 * @param base Serial instance
 * @param instance Serial instance if needed by target.
 * @param a Byte to write
 */
void serial_putchar(Serial base, void * instance, uint8_t a);

/**
 * @brief Sets internal buffer for serial to read from
 * @param base Serial instance
 * @param buffer Buffer to read into
 * @param size Number of bytes the buffer can hold
 */
void serial_attach_buffer(Serial base, uint8_t * buffer, uint16_t size);

/** @} */

/** @} */

#include "serial_private.h"

#endif //DRIVERS_SERIAL_H
