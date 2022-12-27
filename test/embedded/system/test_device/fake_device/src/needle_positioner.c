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
    ServerApp server;
    needle_positioner_init_t * ctx;
    uint8_t rx_buffer[STM32_USART1_RX_BUFFER_SIZE];

} self = {0};

static void
write_handler(void * device, uint8_t * bytes, uint16_t size)
{
    Serial d = (Serial) device;
    serial_write(d, bytes, size);
}

NeedlePositioner
needle_positioner_create(needle_positioner_init_t * params)
{
    self.ctx              = params;
    app_init_t app_params = {
            .address = MODBUS_ADDRESS,
            .rx_buffer=self.rx_buffer,
            .serial_device = self.ctx->serial,
            .write_handler = write_handler,
            .restart = 0,
    };
    discrete_inputs_create(&tables[DI_TABLE], &self.ctx);
    coils_create(&tables[COIL_TABLE], &self.ctx);
    input_registers_create(&tables[IR_TABLE], &self.ctx);
    holding_registers_create(&tables[HR_TABLE], &self.ctx);
    self.server = server_create(&app_params);
    return &self;
}

void
needle_positioner_run(NeedlePositioner positioner)
{
    server_update(positioner->server);
}
