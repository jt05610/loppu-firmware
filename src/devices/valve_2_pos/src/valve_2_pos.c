/**
  ******************************************************************************
  * @file   force_pump.c
  * @author jtaylor
  * @date   21 Mar 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "config.h"
#include "valve_2_pos.h"

#include "data_model/coils.h"

/**
 * @brief Any data needed to run force_pump
 */
static valve_2_pos_t self = {0};

Device
valve_2_pos_create(valve_2_pos_t * params)
{
    self.base.hal = params->hal;
    coils_create(&self.tables[COIL_TABLE], &self);
    self.base.model       = datamodel_create(self.tables);
    app_init_t app_params = {
            .address = MODBUS_ADDRESS,
            .serial = params->hal->serial,
            .ser_inst = params->uart_inst,
            .timer = params->hal->timer,
            .tim_inst = params->tim_inst,
            .data_model = self.base.model
    };
    self.base.server = server_create(&app_params);
    return &self.base;
}

void
valve_2_pos_run(Device device)
{
    server_update(device->server);
}

