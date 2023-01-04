//
// Created by taylojon on 11/23/2022.
//

#ifndef INJECTOR_PRIMARY_TABLE_PRIVATE_H
#define INJECTOR_PRIMARY_TABLE_PRIVATE_H

#ifndef INJECTOR_PRIMARY_TABLE_H
#include "primary_table.h"
#endif

typedef void (* pt_read_t)(sized_array_t * dest);

typedef void (* pt_write_t)(uint16_t value);

typedef struct primary_table_interface_t
{
    pt_read_t * read;

    pt_write_t * write;

} primary_table_interface_t;

typedef struct primary_table_t
{
    PrimaryTableInterface vtable;

} primary_table_t;

#endif //INJECTOR_PRIMARY_TABLE_PRIVATE_H
