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
 * @addtogroup STM32G0xx
 * @{
 */

/**
 * @defgroup STM32G0xx_Serial Universal synchronous/asynchronous
 *           receiver transmitter (USART)
 * @brief Serial implementation for STM32g031xx microcontroller
 * @{
 */

#include "serial.h"
#include "stm32g0xx_ll_usart.h"

/** @brief Struct for RX interrupt handlers */
typedef struct rx_callback_t
{
    USART_TypeDef * instance;      /**< @brief USART instance */
    void          * data;          /**< @brief Any data to pass to callback*/
    void (* call)(void * data);    /**< @brief Run callback with passed data */
} rx_callback_t;

/**
 * @brief Creates STM32 serial instance.
 * @return @ref Serial instance for stm32 peripherals.
 */
Serial stm32_serial_create();

/**
 * @brief Sets function to run once a receive timeout is triggered.
 * @param instance serial instance if need by target mcu.
 * @param cb callback function to run.
 * @param to_pass data to pass to callback if needed.
 */
void
stm32_serial_set_rto_cb(void * instance, rx_callback_t * cb, void * to_pass);

/** @) */

/** @) */

#endif //INJECTOR_STM32_SERIAL_H
