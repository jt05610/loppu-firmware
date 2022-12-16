//
// Created by Jonathan Taylor on 5/8/22.
//

#ifndef MICROFLUIDICSYSTEM_DATALINKSPY_H
#define MICROFLUIDICSYSTEM_DATALINKSPY_H

#include ".private/datalink.h"

void dl_spy_create(Datalink base, uint8_t address);

void dl_spy_create_pdu(
        uint8_t address, uint8_t func_code, uint8_t * data,
        size_t size,
        uint16_t crc, SerialPDU dest
);

uint8_t dl_spy_error_count();

uint8_t dl_spy_get_delimiter();

void dl_spy_set_error_counter(
        dl_counter_t counter,
        uint16_t value
);

#endif //MICROFLUIDICSYSTEM_DATALINKSPY_H
