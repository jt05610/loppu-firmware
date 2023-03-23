/**
  ******************************************************************************
  * @file   needle_mover.c
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
#include "needle_mover.h"
#include "linear_axis.h"
#include "stepper.h"

#include "data_model/coils.h"
#include "data_model/input_registers.h"
#include "data_model/holding_registers.h"

#define N_TABLES 4     /**< @brief Number of implemented data model tables    */

/**
 * @brief Any data needed to run needle_mover
 */
static struct needle_mover_t
{
    device_t        base;
    primary_table_t tables[4];
    /* Feel free to add below here: */

} self = {0};

Device
needle_mover_create(
        Peripherals hal, void * uart_inst, void * tim_inst,  StepDir stepdir, Axis axis)
{
    self.base.hal = hal;
    coils_create(&self.tables[COIL_TABLE], &self.base, axis);
    input_registers_create(&self.tables[IR_TABLE], &self.base, stepdir, axis);
    holding_registers_create(&self.tables[HR_TABLE], &self.base, stepdir, axis);
    self.base.model       = datamodel_create(self.tables);
    app_init_t app_params = {
            .address = MODBUS_ADDRESS,
            .serial = hal->serial,
            .ser_inst = uart_inst,
            .timer = hal->timer,
            .tim_inst = tim_inst,
            .data_model = self.base.model
    };
    self.base.server = server_create(&app_params);
    return &self.base;
}

void
needle_mover_run(Device device)
{
    while (1) {
        server_update(device->server);
    }
}

