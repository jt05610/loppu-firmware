/**
  ******************************************************************************
  * @file   needle_positioner.c
  * @author Jonathan Taylor
  * @date   11 Dec 2022
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "device.h"
#include "needle_positioner.h"

#include "data_model/discrete_inputs.h"
#include "data_model/coils.h"
#include "data_model/input_registers.h"
#include "data_model/holding_registers.h"
#include "config.h"

#define N_TABLES 4

static primary_table_t tables[N_TABLES];

static struct needle_positioner_t
{
    device_t base;

} self = {0};

NeedlePositioner
needle_positioner_create(Peripherals hal, void * uart_inst, void * tim_inst)
{
    self.base.hal = hal;
    app_init_t app_params = {
            .address = MODBUS_ADDRESS,
            .serial = hal->serial,
            .ser_inst = uart_inst,
            .timer = hal->timer,
            .tim_inst = tim_inst
    };
    self.base.server = server_create(&app_params);
    discrete_inputs_create(&tables[DI_TABLE]);
    coils_create(&tables[COIL_TABLE]);
    input_registers_create(&tables[IR_TABLE]);
    holding_registers_create(&tables[HR_TABLE]);
    return &self;
}

void
needle_positioner_run(NeedlePositioner positioner)
{
    server_update(positioner->base.server);
}
