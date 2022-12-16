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
#include "fake_device.h"

#include "data_model/discrete_inputs.h"
#include "data_model/coils.h"
#include "data_model/input_registers.h"
#include "data_model/holding_registers.h"

#define N_TABLES 4

static primary_table_t tables[N_TABLES];

static uint8_t rx_buffer[256];

static void
write_handler(void * device, uint8_t * bytes, uint16_t size)
{

}

static void
fake_restart()
{

}

void
fake_device_create(FakeDevice base)
{
    app_init_t app_params = {
            .address = FAKE_ADDRESS,
            .rx_buffer=rx_buffer,
            .serial_device = 0,
            .write_handler = write_handler,
            .restart = fake_restart,
    };
    discrete_inputs_create(&tables[DI_TABLE], base);
    coils_create(&tables[COIL_TABLE], base);
    input_registers_create(&tables[IR_TABLE], base);
    holding_registers_create(&tables[HR_TABLE], base);
    base->server = server_create(&app_params);
    server_attach_device(base->server, base, tables);
    for (uint8_t i = 0; i < 4; i ++)
        base->values[i] = 0;
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

PrimaryTable
fake_device_get_tables()
{
    return tables;
}
