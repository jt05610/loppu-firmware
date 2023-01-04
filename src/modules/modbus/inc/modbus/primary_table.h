//
// Created by taylojon on 11/23/2022.
//

#ifndef INJECTOR_PRIMARY_TABLE_H
#define INJECTOR_PRIMARY_TABLE_H

#include "project_types.h"

typedef struct primary_table_t           * PrimaryTable;
typedef struct primary_table_interface_t * PrimaryTableInterface;

void
primary_table_read(PrimaryTable table, uint16_t address, sized_array_t * dest);

void primary_table_write(PrimaryTable table, uint16_t address, uint16_t value);

#include "primary_table_private.h"

#endif //INJECTOR_PRIMARY_TABLE_H