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

#ifndef MICROFLUIDICSYSTEM_SERIAL_H
#define MICROFLUIDICSYSTEM_SERIAL_H

#include "stdbool.h"
#include <stdint.h>

typedef struct serial_t           * Serial;
typedef struct serial_interface_t * SerialInterface;


/**
 * @brief Opens serial device
 * @param base Serial instance
 */
void serial_open(Serial base);

/**
 * @brief Closes serial device
 * @param base Serial instance
 */
void serial_close(Serial base);

/**
 * @brief Read data from serial port
 * @param base Serial instance
 * @param dest buffer to read data into
 * @return number of read bytes
 */
uint16_t serial_read(Serial base, uint8_t * dest);

/**
 * @brief Writes data to serial port
 * @param base Serial instance
 * @param data data to write
 * @param size number of bytes to write
 */
void serial_write(Serial base, uint8_t * data, uint16_t size);

/**
 * @brief Sets internal buffer for serial to read from
 * @param base Serial instance
 * @param buffer Buffer to read into
 * @param size Number of bytes the buffer can hold
 */
void serial_attach_buffer(Serial base, uint8_t * buffer, uint16_t size);

#include "serial_private.h"

#endif //MICROFLUIDICSYSTEM_SERIAL_H
