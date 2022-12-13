//
// Created by Jonathan Taylor on 5/8/22.
//

#include "datalink_spy.h"

static struct datalink_spy_t
{
    uint8_t error_count;
    uint8_t error_counters[N_ERROR_COUNTERS];
    uint8_t address;
} self = {0};

static void
handle_error()
{
    self.error_count++;
}

static void
spy_reset_comm_log()
{
    self.error_count = 0;
}

static void
spy_clear_counters()
{
    for (uint8_t i = 0; i < ERROR_COUNTERS; i++)
    {
        self.error_counters[i] = 0x00;
    }
}

static uint8_t
spy_error_decimal(dl_counter_t error)
{
    return error - 11;
}

static uint16_t
spy_error_counter(dl_counter_t counter)
{
    return self.error_counters[spy_error_decimal(counter)];
}

static void
spy_clear_counter(dl_counter_t counter)
{
    self.error_counters[spy_error_decimal(counter)] = 0x00;
}

static datalink_interface_t client_dl_interface = {
        .update=0,
        .handle_error=handle_error,
        .reset_comm_log=spy_reset_comm_log,
        .get_counter=spy_error_counter,
        .clear_counters=spy_clear_counters,
        .clear_counter=spy_clear_counter
};

void
dl_spy_create(Datalink base, uint8_t address)
{
    base->vtable     = &client_dl_interface;
    self.error_count = 0;
    self.address     = address;
}

void
dl_spy_create_pdu(
        uint8_t address,
        uint8_t func_code,
        uint8_t * data,
        size_t size,
        uint16_t crc,
        SerialPDU dest
)
{
    dest->pdu->func_code  = func_code;
    dest->pdu->data.size  = size;
    dest->pdu->data.bytes = data;
    dest->address         = address;
    dest->crc             = crc;
}

uint8_t
dl_spy_error_count(Datalink base)
{
    return self.error_count;
}

void
dl_spy_set_error_counter(
        dl_counter_t counter,
        uint16_t value
)
{
    self.error_counters[spy_error_decimal(counter)] = value;
}