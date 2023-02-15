/**
  ******************************************************************************
  * @file   serial_adv_config.h
  * @author Jonathan Taylor
  * @date   2/14/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_SERIAL_ADV_CONFIG_H
#define INJECTOR_SERIAL_ADV_CONFIG_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup STM32G0xx_SerialConfig Serial config
 * @ingroup STM32G0xx_Serial
 * @ingroup STM32G0xx_DefaultConfig
 * @brief Macros to implement stm32g031xx serial peripheral.
 * @{
 */
#include "stm32g0xx_ll_usart.h"


#if STM32_ENABLE_USART1
/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART1Config USART1 config
 * @brief USART1 configuration
 * @{
 */

/** @brief USART1 rx buffer size */
#define STM32_USART1_RX_BUFFER_SIZE     256

/** @brief Prescaler for USART1 */
#define STM32_USART1_PRESCALER_VALUE    LL_USART_PRESCALER_DIV1

/** @brief USART1 Baud rate */
#define STM32_USART1_BAUD_RATE          115200

/** @brief USART1 data width in bits */
#define STM32_USART1_DATA_WIDTH         LL_USART_DATAWIDTH_8B

/** @brief USART1 number of stop bits */
#define STM32_USART1_STOP_BITS          LL_USART_STOPBITS_1

/** @brief USART1 parity */
#define STM32_USART1_PARITY             LL_USART_PARITY_NONE

/** @brief Transfer direction for USART1 */
#define STM32_USART1_TRANSFER_DIRECTION LL_USART_DIRECTION_TX_RX

/** @brief USART1 hardware flow control to use */
#define STM32_USART1_HARDWARE_FC        LL_USART_HWCONTROL_NONE

/** @brief Oversampling factor for USART1. */
#define STM32_USART1_OVER_SAMPLING      LL_USART_OVERSAMPLING_16

/** @brief Enables FIFO mode for USART1 */
#define STM32_USART1_FIFO               1

/** @brief Enables RS485 mode for USART1 */
#define STM32_USART1_RS485              1

/** @brief USART1 DE Signal polarity */
#define STM32_USART1_DE_POLARITY        LL_USART_DE_POLARITY_HIGH

/** @brief USART1 DE assertion time */
#define STM32_USART1_DE_ASSERT_TIME     0x08

/** @brief USART 1 DE deassertion time */
#define STM32_USART1_DE_DEASSERT_TIME   0x08

/** @brief Turn on STM32 Async mode for USART1 */
#define STM32_USART1_ASYNC              1

/** @brief Enable STM32 RTO interrupt */
#define STM32_USART1_RTO_ENABLE         1

/** @brief Enable STM32 IDLE interrupt */
#define STM32_USART1_IDLE_ENABLE        0

/** @brief Enable STM32 TC interrupt */
#define STM32_USART1_TC_ENABLE          1

/** @brief Enable STM32 PE interrupt */
#define STM32_USART1_PE_ENABLE          0

/** @brief Enable STM32 character match interrupt */
#define STM32_USART1_CM_ENABLE          0

/** @brief Enable STM32 ERROR interrupt */
#define STM32_USART1_ERROR_ENABLE       0

/** @brief bits time to trigger rx timeout interrupt */
#define STM32_USART1_RX_TIMEOUT         10

/** @) */
#endif // STM32_ENABLE_USART1

#if STM32_ENABLE_USART2
/**
  ******************************************************************************
 * @defgroup STM32G0xx_USART2Config USART2 config
 * @brief USART2 configuration
 * @{
 */

/** @brief USART2 rx buffer size */
#define STM32_USART2_RX_BUFFER_SIZE     16

/** @brief Prescaler for USART2 */
#define STM32_USART2_PRESCALER_VALUE    LL_USART_PRESCALER_DIV1

/** @brief USART2 Baud rate */
#define STM32_USART2_BAUD_RATE          19200

/** @brief USART2 data width in bits */
#define STM32_USART2_DATA_WIDTH         LL_USART_DATAWIDTH_8B

/** @brief USART2 number of stop bits */
#define STM32_USART2_STOP_BITS          LL_USART_STOPBITS_1

/** @brief USART2 parity */
#define STM32_USART2_PARITY             LL_USART_PARITY_NONE

/** @brief Transfer direction for USART2 */
#define STM32_USART2_TRANSFER_DIRECTION LL_USART_DIRECTION_TX_RX

/** @brief USART2 hardware flow control to use */
#define STM32_USART2_HARDWARE_FC        LL_USART_HWCONTROL_NONE

/** @brief Oversampling factor for USART2. */
#define STM32_USART2_OVER_SAMPLING      LL_USART_OVERSAMPLING_16

/** @brief Enables FIFO mode for USART21 */
#define STM32_USART2_FIFO               0

/** @brief Enables RS485 mode for USART2 */
#define STM32_USART2_RS485              0

#if STM32_USART2_RS485
/** @brief USART2 DE Signal polarity */
#define STM32_USART2_DE_POLARITY        LL_USART_DE_POLARITY_HIGH

/** @brief USART2 DE assertion time */
#define STM32_USART2_DE_ASSERT_TIME     0x08

/** @brief USART 1 DE deassertion time */
#define STM32_USART2_DE_DEASSERT_TIME   0x08

#endif // STM32_USART2_RS485

/** @brief Turn on STM32 Async mode for USART2 */
#define STM32_USART2_ASYNC              1

/** @brief Enable STM32 RTO interrupt */
#define STM32_USART2_IDLE_ENABLE        0

/** @brief Enable STM32 TC interrupt */
#define STM32_USART2_TC_ENABLE          0

/** @brief Enable STM32 PE interrupt */
#define STM32_USART2_PE_ENABLE          0

/** @brief Enable STM32 ERROR interrupt */
#define STM32_USART2_ERROR_ENABLE       0

/** @) */
#endif // STM32_ENABLE_USART2

/** @) */

#ifdef __cplusplus
}
#endif

#endif //INJECTOR_SERIAL_ADV_CONFIG_H
