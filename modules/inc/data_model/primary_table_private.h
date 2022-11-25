//
// Created by taylojon on 11/23/2022.
//

#ifndef INJECTOR_PRIMARY_TABLE_PRIVATE_H
#define INJECTOR_PRIMARY_TABLE_PRIVATE_H

#ifndef INJECTOR_PRIMARY_TABLE_H
#include "primary_table.h"
#endif

typedef struct primary_table_interface_t
{
    uint16_t (* read)(PrimaryTable table, uint16_t address);

    void (* write)(PrimaryTable table, uint16_t address, uint16_t value);

} primary_table_interface_t;

typedef struct primary_table_t
{
    PrimaryTableInterface vtable;

} primary_table_t;
#endif //INJECTOR_PRIMARY_TABLE_PRIVATE_H
