/**
  ******************************************************************************
  * @file   data_model.c
  * @author Jonathan Taylor
  * @date   12/4/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "../inc/public/modbus/data_model.h"
#include "../inc/public/modbus/util.h"


void
datamodel_create(DataModel base, PrimaryTable tables)
{
    base->tables = tables;
}

static void read(
        DataModel dm, uint8_t table, ModbusPDU pdu, sized_array_t * dest);

static void write(
        DataModel dm, uint8_t table, ModbusPDU pdu, sized_array_t * dest);

typedef void (* handler_t)(
        DataModel dm, uint8_t table, ModbusPDU pdu, sized_array_t * dest);

typedef struct dm_action_t
{
    handler_t handler;
    uint8_t   table;

} dm_action_t;

static dm_action_t handlers[6] = {
        {read,  COIL_TABLE},
        {read,  DI_TABLE},
        {read,  HR_TABLE},
        {read,  IR_TABLE},
        {write, COIL_TABLE},
        {write, HR_TABLE},
};

void
datamodel_handle(DataModel base, ModbusPDU pdu, sized_array_t * result)
{
    dm_action_t * action;
    if (pdu->func_code < 0x07)
    {
        action = &handlers[pdu->func_code - 1];
        action->handler(base, action->table, pdu, result);
    }
}

static void
read(DataModel dm, uint8_t table, ModbusPDU pdu, sized_array_t * dest)
{
    primary_table_read(
            &dm->tables[table],
            dm->device,
            UINT8_TO_UINT16(pdu->data.bytes, 0),
            dest
    );
    dest->size = (table >> 1) + 1;
}

static void
write(DataModel dm, uint8_t table, ModbusPDU pdu, sized_array_t * dest)
{
    primary_table_write(
            &dm->tables[table],
            dm->device,
            UINT8_TO_UINT16(pdu->data.bytes, 0),
            UINT8_TO_UINT16(pdu->data.bytes, 2)
    );
    dest->size  = 0;
}

