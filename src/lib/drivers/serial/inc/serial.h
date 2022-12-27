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
#include "buffer/circular_buffer.h"

/**
 * @brief Pointer to @ref serial_base_t.
 */
typedef struct serial_base_t * Serial;

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
 * @brief Read pending data from serial port
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
 * @return Unsigned version of given char.
 */
uint8_t serial_putchar(Serial base, void * instance, char a);

/**
 * @brief Sets internal buffer for serial to read from
 * @param base Serial instance
 * @param buffer Instantiated circular buffer to read into
 */
void serial_attach_buffer(Serial base, circ_buf_t * buffer);

/**
 * @brief Transfers from passed source buffer into serial's circular buffer
 * @param base Serial instance
 * @param src Buffer to transfer from
 * @return true if okay, false if error occurred
 */
bool serial_buffer_transfer(Serial base, circ_buf_t * src);

uint16_t serial_available(Serial base, void * instance);

void serial_clear(Serial base, void * instance);

void serial_register_rx_callback(Serial base, void * instance, void (*cb)(void));

/** @} */

/** @} */

#include "serial_private.h"

#endif //DRIVERS_SERIAL_H
