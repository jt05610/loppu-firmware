//
// Created by taylojon on 11/23/2022.
//
#include "modbus/primary_table.h"
#include "device.h"

void
primary_table_read(PrimaryTable table, uint16_t address, sized_array_t * dest)
{
    if (table && table->vtable && table->vtable->read)
    {
        table->vtable->read[address](dest);
    }
}

void
primary_table_write(PrimaryTable table, uint16_t address, uint16_t value)
{
    if (table && table->vtable && table->vtable->write)
    {
        table->vtable->write[address](value);
    }
}
