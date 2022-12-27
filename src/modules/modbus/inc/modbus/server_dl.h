//
// Created by Jonathan Taylor on 5/8/22.
//
#ifndef MICROFLUIDICSYSTEM_CLIENTAPPLICATION_H
#define MICROFLUIDICSYSTEM_CLIENTAPPLICATION_H

#if 0
#include "datalink.h"
#include "types.h"

void
server_dl_create(
        Datalink base,
        uint8_t address,
        volatile uint8_t * rx_buffer,
        ModbusPDU pdu,
        void * serial_device,
        write_handler_t write_handler
);

uint16_t server_dl_get_counter(dl_counter_t error);

uint8_t server_dl_get_exception_status();

void server_dl_format_response(sized_array_t * result);

void server_dl_send_response();

void server_dl_set_exception_status(uint8_t status, uint8_t output);

uint8_t server_dl_get_address();

void server_dl_set_diag_register(uint16_t value);

uint16_t server_dl_get_diag_register();

void server_dl_clear_counters();

void server_dl_set_counter(dl_counter_t counter, uint16_t value);
#endif
#endif //MICROFLUIDICSYSTEM_CLIENTAPPLICATION_H