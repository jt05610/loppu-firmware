//
// Created by taylojon on 11/23/2022.
//
#include "data_model/primary_table.h"

uint16_t
primary_table_read(PrimaryTable table, uint16_t address)
{
    if (table && table->vtable && table->vtable->read)
    {
        return table->vtable->read[address](table);
    }
    return 0xFFFF;
}

void
primary_table_write(PrimaryTable table, uint16_t address, uint16_t value)
{
    if (table && table->vtable && table->vtable->write)
    {
        table->vtable->write[address](table, value);
    }
}
