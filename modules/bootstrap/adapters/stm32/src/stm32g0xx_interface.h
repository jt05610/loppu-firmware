/**
  ******************************************************************************
  * @file   stm32g0xx_interface.h
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  STM32G0xx interface header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_STM32G0XX_INTERFACE_H
#define INJECTOR_STM32G0XX_INTERFACE_H

#include "bootstrap.h"
#include "stm32g031xx.h"
#include <sys/cdefs.h>

/**@addtogroup Bootstrap
 * @{
 */

/** @addtogroup Adapters
 * @{
 */

/**
 * @defgroup STM32G0xx
 * @brief STM32G0xx HAL implementation.
 * @{
 */

/**
 * @brief Return type for interrupt functions to avoid compiler warnings.
 */
#define __INTERRUPT __attribute__((unused)) void

/**
 * @brief STM32G0xx system clock tick.
 */
#ifndef STM32_SYS_TICK
#define STM32_SYS_TICK 16000000
#endif

/**
 * @brief Parameters to initialize STM32G0xx HAL.
 */
typedef struct stm32_init_t
{
    uint8_t * rx_buffer;     /**< @brief Buffer to receive serial messages. */
    uint16_t rx_buffer_size; /**< @brief Size of @ref rx_buffer. */
} stm32_init_t;

/**
 * @brief  Creates peripheral implementation for stm32g0xx.
 * @param params pointer to @ref stm32init_t.
 * @return STM32G0xx implemented @ref Peripherals.
 */
Peripherals stm32_dependency_injection(void * params);


/**
 * Copy volatile buffer from one to another
 * @param dest destination buffer
 * @param src source buffer
 * @param n number of bytes to transfer
 */
static inline volatile void
* copy(
        volatile uint8_t * restrict dest,
        const volatile uint8_t * restrict src,
        size_t n)
{
    const volatile uint8_t * src_c  = src;
    volatile uint8_t       * dest_c = dest;

    while (n > 0)
    {
        n--;
        dest_c[n] = src_c[n];
    }
    return dest;
}
/** @} */

/** @} */
/** @} */

#endif //INJECTOR_STM32G0XX_INTERFACE_H
