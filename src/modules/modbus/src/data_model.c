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

#include <string.h>

#include "modbus/util.h"

static data_model_t self = {0};

DataModel
datamodel_create(const PrimaryTable tables, device_info_t *device_info) {
    self.tables = tables;
    self.info = device_info;
    return &self;
}

static void read(DataModel dm, uint8_t table, ModbusPDU pdu);

static void write(DataModel dm, uint8_t table, ModbusPDU pdu);

typedef void (*handler_t)(DataModel dm, uint8_t table, ModbusPDU pdu);

typedef struct dm_action_t {
    handler_t handler;
    uint8_t table;
} dm_action_t;

static dm_action_t handlers[6] = {
    {read, COIL_TABLE},
    {read, DI_TABLE},
    {read, HR_TABLE},
    {read, IR_TABLE},
    {write, COIL_TABLE},
    {write, HR_TABLE},
};

void write_object(const uint8_t obj_id, const ModbusPDU dest, const char *value) {
    const uint16_t curLen = dest->data.size;
    const size_t size = strlen(value);
    dest->data.bytes[curLen] = obj_id;
    dest->data.bytes[curLen + 1] = size;
    for (uint8_t i = 0; i < size; i++) {
        dest->data.bytes[curLen + 2 + i] = value[i];
    }
    dest->data.bytes[5] += 1;
    dest->data.size += 2 + size;
}

void init_device_info(const ModbusPDU dest) {
    dest->data.bytes[2] = 0x01; // Conformity level
    dest->data.bytes[3] = 0x00; // More flags
    dest->data.bytes[4] = 0x00; // Next object id
    dest->data.bytes[5] = 0x00; // Number of objects
    dest->data.size = 6;
}

void basic_info_handle(const DataModel base, const ModbusPDU pdu) {
    write_object(0x00, pdu, base->info->vendor_name);
    write_object(0x01, pdu, base->info->product_code);
    write_object(0x02, pdu, base->info->major_minor_revision);
    write_object(0x81, pdu, base->info->serial_number);
}

void regular_info_handle(const DataModel base, const ModbusPDU pdu) {
    write_object(0x03, pdu, base->info->vendor_url);
    write_object(0x04, pdu, base->info->product_name);
    write_object(0x05, pdu, base->info->model_name);
    write_object(0x06, pdu, base->info->user_application_name);
}

void extended_info_handle(const DataModel base, const ModbusPDU pdu) {
    write_object(0x80, pdu, base->info->device_schema);
}

void read_object(const DataModel base, const uint8_t obj_id, const ModbusPDU pdu) {
    switch (obj_id) {
        case 0x00:
            write_object(0x00, pdu, base->info->vendor_url);
            break;
        case 0x01:
            write_object(0x01, pdu, base->info->product_name);
            break;
        case 0x02:
            write_object(0x02, pdu, base->info->major_minor_revision);
            break;
        case 0x03:
            write_object(0x03, pdu, base->info->vendor_url);
            break;
        case 0x04:
            write_object(0x04, pdu, base->info->product_name);
            break;
        case 0x05:
            write_object(0x05, pdu, base->info->model_name);
            break;
        case 0x06:
            write_object(0x06, pdu, base->info->user_application_name);
            break;
        case 0x80:
            write_object(0x80, pdu, base->info->device_schema);
            break;
        default:
            break;
    }
}

void
device_id_handle(const DataModel base, const ModbusPDU pdu) {
    const uint8_t mei_type = pdu->data.bytes[0];
    if (mei_type != 0x0E) {
        return;
    }
    const uint8_t read_code = pdu->data.bytes[1];
    const uint8_t obj_id = pdu->data.bytes[2];
    init_device_info(pdu);
    if (read_code == 0x01) {
        basic_info_handle(base, pdu);
        return;
    }
    if (read_code == 0x02) {
        regular_info_handle(base, pdu);
        return;
    }
    if (read_code == 0x03) {
        extended_info_handle(base, pdu);
        return;
    }
    if (read_code == 0x04) {
        init_device_info(pdu);
    }
}

void
datamodel_handle(const DataModel base, const ModbusPDU pdu) {
    if (pdu->func_code < 0x07) {
        const dm_action_t *action = &handlers[pdu->func_code - 1];
        action->handler(base, action->table, pdu);
    }
    if (pdu->func_code == 0x2B) {
        device_id_handle(base, pdu);
    }
}

static void
read(const DataModel dm, const uint8_t table, const ModbusPDU pdu) {
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
write(const DataModel dm, const uint8_t table, const ModbusPDU pdu) {
    primary_table_write(
        &dm->tables[table],
        UINT8_TO_UINT16(pdu->data.bytes, 0),
        &pdu->data
    );
}
