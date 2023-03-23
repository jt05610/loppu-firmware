/**
  ******************************************************************************
  * @file   stm32_spi.h
  * @author Jonathan Taylor
  * @date   22 Mar 2023
  * @brief  SPI header for STM32G031xx MCU
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_STM32_SPI_H
#define INJECTOR_STM32_SPI_H


/**
 * @defgroup STM32G0xx_SPI Serial peripheral interface (SPI)
 * @ingroup STM32G0xx
 * @brief SPI implementation for STM32G0xx MCU
 */

#include "spi.h"

/**
 * @brief Creates SPI for stm32
 * @ingroup STM32G0xx_SPI
 * @return Instantiated SPI
 */
SPI stm32_spi_create();

#endif //INJECTOR_STM32_SPI_H
