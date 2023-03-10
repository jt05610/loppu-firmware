/**
  ******************************************************************************
  * @file   stm32_serial.h
  * @author Jonathan Taylor
  * @date   12/14/22
  * @brief  STM32G031xx serial interface header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_STM32_SERIAL_H
#define INJECTOR_STM32_SERIAL_H

#include "default/serial_config.h"

/**
 * @defgroup STM32G0xx_Serial Universal synchronous/asynchronous
 *           receiver transmitter (USART)
 * @ingroup STM32G0xx
 * @brief Serial implementation for STM32g031xx microcontroller
 * @{
 */

#include "serial.h"
#include "stm32g0xx_ll_usart.h"
#include "buffer/circular_buffer.h"

/**
 * @brief Creates STM32 serial instance.
 * @return @ref Serial instance for stm32 peripherals.
 */
Serial stm32_serial_create();

/**
 * @brief Gets USART1 RX buffer
 * @return USART1 RX buffer
 */
uint8_t * stm32_get_usart1_rx_buffer();

/**
 * @brief Gets USART1 RX circular buffer
 * @return USART1 RX circular buffer
 */
circ_buf_t * stm32_get_usart1_rx_circ_buffer();

/**
 * @brief Gets USART1 TX buffer
 * @return USART1 TX buffer
 */
uint8_t * stm32_get_usart1_tx_buffer();

/**
 * @brief Gets USART2 RX buffer
 * @return USART2 RX buffer
 */
uint8_t * stm32_get_usart2_rx_buffer();

/**
 * @brief Gets USART2 TX buffer
 * @return USART2 TX buffer
 */
uint8_t * stm32_get_usart2_tx_buffer();

/**
 * @brief  See if there is data in rx buffer
 * @return Whether or not there is new data
 */
bool stm32_serial_new_data();


/** @) */


#endif //INJECTOR_STM32_SERIAL_H
