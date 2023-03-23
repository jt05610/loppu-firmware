/**
  ******************************************************************************
  * @file   spi.h
  * @author Jonathan Taylor
  * @date   22 Mar 2023
  * @brief  spi abstraction header
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_SPI_H
#define DRIVERS_SPI_H

#include <stdint.h>

/**
 * @defgroup SPI
 * @ingroup Peripherals
 * @brief SPI abstraction library.
 * @details Implement functions in spi_interface_t to hook up with target mcu
 * @{
 */

/**
 * @brief SPI is a pointer to a privately defined spi instance.
 */
typedef struct spi_t * SPI;

/**
 * @brief Opens SPI interface
 * @param self SPI instance
 * @param spi_inst If Target mcu has multiple SPIs, this is to select which one
 */
void spi_open(SPI self, void * spi_inst);

/**
 * @brief Closes SPI
 * @param self SPI instance
 * @param spi_inst If Target mcu has multiple SPIs, this is to select which one
 */
void spi_close(SPI self, void * spi_inst);

/**
 * @brief reads from SPI
 * @param self SPI instance
 * @param spi_inst If Target mcu has multiple SPIs, this is to select which one
 * @param dest Buffer to read into
 * @return number of bytes read into buffer
 */
uint16_t spi_read(SPI self, void * spi_inst, uint8_t * dest);

/**
 * @brief writes to SPI
 * @param self SPI instance
 * @param spi_inst If Target mcu has multiple SPIs, this is to select which one
 * @param data Buffer to write from
 * @param size size of buffer
 * @return number of bytes written to SPI
 */
uint16_t spi_write(SPI self, void * spi_inst, uint8_t * data, uint16_t size);

/** @} */

#include "spi_private.h"

#endif //DRIVERS_SPI_H
