/**
  ******************************************************************************
  * @file   bootstrap.h
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  Bootstrap library header file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_BOOTSTRAP_H
#define INJECTOR_BOOTSTRAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "peripherals.h"

/** @addtogroup Modules
 * @{
 */

/**
 * @defgroup Bootstrap
 * @brief Hardware abstraction layer dependency injection library.
 * @{
*/

/**
 * @brief Function prototype for retrieving hardware abstraction layer for
 *        target mcu.
 */
typedef Peripherals(* adapter_t)(void * params);

/**
 * @brief Dependency injection function .
 * @param adapter Adapter function specific for target mcu.
 * @param params Any params needed for adapter.
 * @return @ref Peripherals for target mcu.
 */
Peripherals bootstrap(adapter_t adapter, void * params);

/** @} */

/** @} */

#ifdef __cplusplus
};
#endif

#endif //INJECTOR_BOOTSTRAP_H
