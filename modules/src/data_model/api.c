/**
  ******************************************************************************
  * @file   api.c
  * @author Jonathan Taylor
  * @date   11/18/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "data_model/api.h"
#include "discrete_inputs.h"

uint16_t
api_read(api_t * base, uint32_t address)
{
    return datamodel_read(base->data_model, address);
}


uint16_t
api_write(api_t * base, uint32_t address, uint16_t value)
{
    address = address % 10000;
    return datamodel_write(base->data_model, address, value);
}

void
api_create(api_t * base, DataModel data_model)
{
    base->modbus_conf.devaddr    = ADDR;
    base->modbus_conf.device     = (void *) 0;
    base->modbus_conf.discrete     = N_DISCRETE_INPUTS;
    base->modbus_conf.sendbuf    = base->send_buffer;
    base->modbus_conf.sendbuf_sz = RX_BUFFER_SIZE;
    base->modbus_conf.recvbuf    = base->receive_buffer;
    base->modbus_conf.recvbuf_sz = RX_BUFFER_SIZE;
    base->modbus_conf.read       = api_read_handler;
    base->modbus_conf.write      = api_write_handler;
    base->modbus_conf.send       = &api_send_handler;
    base->current_pos            = 0;
    base->target_pos = 0;
    base->data_model             = data_model;
    base->mb                     = mbus_open(&base->modbus_conf);
    base->new_data               = false;
    if (base->mb < 0) base->mb = (mbus_t) MBUS_ERROR;
}

static inline void
mb_handle(API base)
{
    uint16_t go_to     = base->target_pos;
    uint16_t remaining = 0;
    if (base->target_pos >= RX_BUFFER_SIZE)
    {
        go_to     = RX_BUFFER_SIZE;
        remaining = base->target_pos - RX_BUFFER_SIZE;
    }
    for (uint16_t i = base->current_pos; i < go_to; i++)
    {
        mbus_poll(base->mb, base->rx_buffer[i]);
    }
    if (remaining)
    {
        base->current_pos = 0;
        base->target_pos  = remaining;
        mb_handle(base);
    } else {
        base->current_pos = base->target_pos;
    }
}

void api_poll(API base)
{
    if (base->new_data)
    {
        if (base->target_pos != base->current_pos)
        {
            mb_handle(base);
        }
        base->new_data = false;
    }
}
