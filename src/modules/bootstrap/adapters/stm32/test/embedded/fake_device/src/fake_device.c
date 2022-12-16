/**
  ******************************************************************************
  * @file   fake_device.c
  * @author jtaylor
  * @date   12 Dec 2022
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

/**
 * @addtogroup FakeDevice
 * @{
 */
#include "modbus/data_model.h"
#include "fake_device.h"
#include "peripherals.h"

#include "data_model/discrete_inputs.h"
#include "data_model/coils.h"
#include "data_model/input_registers.h"
#include "data_model/holding_registers.h"

#define N_TABLES 4     /**< @brief Number of implemented data model tables    */

/**
 * @brief Any data needed to run device
 */
static struct fake_device_t
{
    /* Do not change! */
    ServerApp server;                  /**< @brief Structure to run server    */
    primary_table_t tables[N_TABLES];  /**< @brief Primary tables             */
    Peripherals hal;                   /**< @brief Hardware abstraction layer */
    /* Feel free to add below here: */
    uint16_t values[4];

} self = {0};


FakeDevice
fake_device_create(Peripherals hal, app_init_t * app_params)
{
    self.hal = hal;

    discrete_inputs_create(&self.tables[DI_TABLE], &self);
    coils_create(&self.tables[COIL_TABLE], &self);
    input_registers_create(&self.tables[IR_TABLE], &self);
    holding_registers_create(&self.tables[HR_TABLE], &self);
    self.server = server_create(app_params);
    server_attach_device(self.server, &self, self.tables);
    for (uint8_t i = 0; i < 4; i ++)
        self.values[i] = 0;
    return &self;
}

void
fake_device_set_value(FakeDevice base, uint8_t table, uint16_t value)
{
    base->values[table-1] = value;
}

uint16_t
fake_device_get_value(FakeDevice base, uint8_t table)
{
    return base->values[table-1];
}

void
fake_device_run(FakeDevice device)
{
    server_update(device->server);
}

PrimaryTable
fake_device_get_tables()
{
    return self.tables;
}

/** @} */
