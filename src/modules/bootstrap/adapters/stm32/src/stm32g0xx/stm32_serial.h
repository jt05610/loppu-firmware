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

/**
 * @addtogroup STM32G0xx
 * @{
 */

/**
 * @defgroup STM32G0xx_Serial
 * @brief Serial implementation for STM32g031xx microcontroller
 * @{
 */

#include "serial.h"
#include "stm32g0xx_ll_usart.h"

/**
 * @defgroup STM32g031xx_SerialConfig
 * @brief Macros to implement stm32g031xx serial peripheral.
 * @{
 */

/**
 * @brief whether to configure and enable USART1 instance
 */
#define STM32_ENABLE_USART1            1

/**
 * @brief whether to configure and enable USART2 instance
 */
#define STM32_ENABLE_USART2            0

/**
 * @brief USART rx buffer size
 */
#define RX_BUFFER_SIZE                  256

/**
 * @brief Prescaler for USART
 */
#define STM32_PRESCALER_VALUE           LL_USART_PRESCALER_DIV1

/**
 * @brief USART Baud rate
 */
#define STM32_BAUD_RATE                 115200

/**
 * @brief USART data width in bits
 */
#define STM32_DATA_WIDTH                LL_USART_DATAWIDTH_8B

/**
 * @brief USART number of stop bits
 */
#define STM32_STOP_BITS                 LL_USART_STOPBITS_1

/**
 * @brief USART Parity
 */
#define STM32_PARITY                    LL_USART_PARITY_NONE

/**
 * @brief Transfer direction for usart
 */
#define STM32_TRANSFER_DIRECTION        LL_USART_DIRECTION_TX_RX

/**
 * @brief Harware flow control to use
 */
#define STM32_HARDWARE_FLOW_CONTROL     LL_USART_HWCONTROL_NONE

/**
 * @brief Oversampling factor for USART.
 */
#define STM32_OVER_SAMPLING             LL_USART_OVERSAMPLING_8

/**
 * @brief Enables FIFO mode for USART1
 */
#define STM32_USART1_FIFO              0

/**
 * @brief Enables FIFO mode for USART2
 */
#define STM32_USART2_FIFO              0

/**
 * @brief Enables RS485 mode for USART 1
 */
#define STM32_USART1_RS485             1

/**
 * @brief DE Signal polarity
 */
#define STM32_DE_POLARITY               LL_USART_DE_POLARITY_HIGH

/**
 * @brief DE assertion time
 */
#define STM32_DE_ASSERTION_TIME         0x08

/**
 * @brief DE deassertion time
 */
#define STM32_DE_DEASSERTION_TIME       0x08

/**
 * @brief Turn on STM32 Async mode for USART1
 */
#define STM32_USART1_ASYNC              1

/**
 * @brief Turn on STM32 Async mode for USART2
 */
#define STM32_USART2_ASYNC              1

/**
 * @brief Enable DMA transfers for RX
 */
#define STM32_USART_RX_DMA              1

/**
 * @brief DMA buffer size
 */
#define STM32_USART_DMA_BUFFER_SIZE     8

/**
 * @brief Enable DMA transfers for TX
 */
#define STM32_USART_TX_DMA              0

/**
 * @brief Enable STM32 RTO interrupt
 */
#define STM32_USART_RTO_ENABLE          1

/**
 * @brief Enable STM32 TC interrupt
 */
#define STM32_USART_TC_ENABLE           1

/**
 * @brief bits time to trigger rx timeout interrupt
 */
#define STM32_RX_TIMEOUT                39

#define RX_DMA          DMA1                /**< DMA instance to use for RX */
#define RX_CHANNEL      LL_DMA_CHANNEL_1    /**< DMA channel to use for RX */
#define RX_PIN          LL_GPIO_PIN_7       /**< GPIO pin to use for RX */
#define RX_PORT         GPIOB               /**< GPIO port to use for RX */

#define TX_DMA          DMA1                /**< DMA instance to use for RX */
#define TX_CHANNEL      LL_DMA_CHANNEL_2    /**< DMA channel to use for RX */
#define TX_PIN          LL_GPIO_PIN_6       /**< GPIO pin to use for RX */
#define TX_PORT         GPIOB               /**< GPIO port to use for RX */

#define RE_PIN          LL_GPIO_PIN_11      /**< GPIO pin for RE */
#define RE_PORT         GPIOA               /**< GPIO port for RE a*/
#define DE_PIN          LL_GPIO_PIN_12      /**< GPIO pin for DE */
#define DE_PORT         GPIOA               /**< GPIO port for DE */

/** @} */

/**
 * @brief Function to call once a USART reception is complete.
 * @param data Any data needed to pass to function.
 * @param n_received Number of bytes received.
 */
typedef void (* rx_complete_callback_t)(void * data, uint16_t n_received);

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
void stm32_serial_set_rto_callback(
        void * instance, rx_complete_callback_t cb, void * to_pass);

/**
 * @brief Retrieves serial rx buffer.
 * @return Pointer to serial rx buffer.
 */
volatile uint8_t * stm32_serial_get_rx_buffer();

/** @) */

/** @) */

#endif //INJECTOR_STM32_SERIAL_H
