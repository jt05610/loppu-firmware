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
#include "force_pump.h"

#include "data_model/discrete_inputs.h"
#include "data_model/coils.h"
#include "data_model/input_registers.h"
#include "data_model/holding_registers.h"

#define N_TABLES 4     /**< @brief Number of implemented data model tables    */

/**
 * @brief Any data needed to run force_pump
 */
static struct force_pump_t
{
    device_t base;
    primary_table_t tables[4];
    /* Feel free to add below here: */

} self = {0};

Device
force_pump_create(Peripherals hal, void * uart_inst, void * tim_inst)
{
    self.base.hal = hal;
    discrete_inputs_create(&self.tables[DI_TABLE], &self.base);
    coils_create(&self.tables[COIL_TABLE], &self.base);
    input_registers_create(&self.tables[IR_TABLE], &self.base);
    holding_registers_create(&self.tables[HR_TABLE], &self.base);
    self.base.model = datamodel_create(self.tables);
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
force_pump_run(Device device)
{
    while(1) {
        server_update(device->server);
    }
}

