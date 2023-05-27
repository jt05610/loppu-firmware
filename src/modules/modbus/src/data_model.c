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

#include "modbus/data_model.h"
#include "modbus/util.h"

static data_model_t self = {0};

DataModel
datamodel_create(PrimaryTable tables)
{
    self.tables = tables;
    return &self;
}

static void read(DataModel dm, uint8_t table, ModbusPDU pdu);

static void write(DataModel dm, uint8_t table, ModbusPDU pdu);

typedef void (* handler_t)(DataModel dm, uint8_t table, ModbusPDU pdu);

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
datamodel_handle(DataModel base, ModbusPDU pdu)
{
    dm_action_t * action;
    if (pdu->func_code < 0x07) {
        action = &handlers[pdu->func_code - 1];
        action->handler(base, action->table, pdu);
    }
    if (pdu->func_code == 0x08) {
        return;
    }
}

static void
read(DataModel dm, uint8_t table, ModbusPDU pdu)
{
    pdu->data.size = UINT8_TO_UINT16(pdu->data.bytes, 2) * (1 + ~(table >> 1));
    primary_table_read(
            &dm->tables[table],
            UINT8_TO_UINT16(pdu->data.bytes, 0),
            &pdu->data
    );
    uint16_t s = pdu->data.size - 2;
    UINT16_TO_UINT8_ARRAY(pdu->data.bytes, 0, s);
}

static void
write(DataModel dm, uint8_t table, ModbusPDU pdu)
{
    primary_table_write(
            &dm->tables[table],
            UINT8_TO_UINT16(pdu->data.bytes, 0),
            UINT8_TO_UINT16(pdu->data.bytes, 2)
    );
}

