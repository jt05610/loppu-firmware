/**
  ******************************************************************************
  * @file   serial_private.h
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  Private serial header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_SERIAL_PRIVATE_H
#define DRIVERS_SERIAL_PRIVATE_H

/** @addtogroup Serial
 * @{
 */

/**
 * @brief Serial interface function data structure.
 */
typedef struct serial_interface_t
{
    /**
     * @brief Opens specified serial instance
     * @param instance Serial instance if needed by target.
     */
    void (* open)(void * instance);

    /**
     * @brief Returns number of bytes ready to be read
     * @param instance Serial instance if needed by target.
     */
    uint16_t (* available)(void * instance);

    /**
     * @brief Clears new data flag
     * @param instance Serial instance if needed by target.
     */
    void (* clear)(void * instance);

    /**
     * @brief Closes specified serial instance
     * @param instance Serial instance if needed by target.
     */
    void (* close)(void * instance);

    /**
     * @brief Read data from serial port to dest.
     * @param instance Serial instance if needed by target.
     * @param dest Buffer to store data into.
     * @return Number of read bytes.
     */
    uint16_t (* read)(void * instance, uint8_t * dest);

    /**
     * @brief Write buffer to serial port.
     * @param instance Serial instance if needed by target.
     * @param data Bytes to write.
     * @param size Number of bytes to write.
     */
    void (* write)(void * instance, uint8_t * data, uint16_t size);

    /**
     * @brief Write single byte to serial port.
     * @param instance Serial instance if needed by target.
     * @param a Bytes to write.
     * @return a as unsigned byte
     */
    uint8_t (* putchar)(void * instance, char a);

    void (* reg_rx_cb)(void * instance, void (* cb)(void));

} serial_interface_t;

/**
 * @brief Base serial data structure.
 */
typedef struct serial_base_t
{
    SerialInterface vtable;         /** @brief Pointer to interface. */
    circ_buf_t * serial_buffer;     /** @brief Circular buffer to store data. */
} serial_base_t;

/** @} */

#endif //DRIVERS_SERIAL_PRIVATE_H
