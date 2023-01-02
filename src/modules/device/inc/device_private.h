/**
  ******************************************************************************
  * @file   device_private.h
  * @author Jonathan Taylor
  * @date   12/26/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_DEVICE_PRIVATE_H
#define INJECTOR_DEVICE_PRIVATE_H

/**
 * @addtogroup Device
 * @{
 */

#include "peripherals.h"
#include "modbus/data_model.h"
#include "modbus/server_app.h"

/**
 * @brief Device structure
 */

typedef struct device_t
{
    Peripherals hal;       /**< @brief Hardware abstraction layer */
    DataModel   model;     /**< @brief Device's data model */
    ServerApp   server;    /**< @brief Server to interact with device */
} device_t;

/** @} */

#endif //INJECTOR_DEVICE_PRIVATE_H
