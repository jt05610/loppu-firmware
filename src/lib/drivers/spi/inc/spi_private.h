/**
  ******************************************************************************
  * @file   spi_private.h
  * @author Jonathan Taylor
  * @date   22 Mar 2023
  * @brief  SPI private structs
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_SPI_PRIVATE_H
#define INJECTOR_SPI_PRIVATE_H

#include <stdint.h>

/** @addtogroup SPI
 * @{
 */

/**
 * @brief SPI interface vtable
 */
typedef struct spi_interface_t
{
    /**
     * @brief Open SPI
     * @param instance instantiated SPI instance.
     */
    void (* open)(void * instance);

    /**
     * @brief Close SPI
     * @param instance instantiated SPI instance.
     */
    void (* close)(void * instance);

    /**
     * @brief read from SPI into destination buffer
     * @param instance instantiated SPI instance.
     * @param dest buffer to read into
     * @return number of bytes read
     */
    uint16_t (* read)(void * instance, uint8_t * dest);

    /**
     * @Brief writes to SPI
     * @param instance instantiated SPI instance
     * @param src buffer to write from
     * @param size number of bytes to write
     * @return number of bytes written
     */
    uint16_t (* write)(void * instance, uint8_t * src, uint16_t size);

    /**
     * @Brief performs read and write operations
     * @param instance instantiated SPI instance
     * @param r buffer to read to
     * @param w buffer to write from
     * @param size number of bytes to write/read
     */
    void (* transact)(void * instance, uint8_t * r, uint8_t * w, uint16_t size);

} spi_interface_t;

/**
 * @brief Base data structure for spi
 */
typedef struct spi_t
{
    spi_interface_t * vtable;       /**< @brief Pointer to interface */
} spi_t;

/** @} */

#endif //INJECTOR_SPI_PRIVATE_H
