//
// Created by taylojon on 11/23/2022.
//

#ifndef INJECTOR_PRIMARY_TABLE_H
#define INJECTOR_PRIMARY_TABLE_H

#include <stdint-gcc.h>

typedef struct primary_table_t           * PrimaryTable;
typedef struct primary_table_interface_t * PrimaryTableInterface;

uint16_t primary_table_read(PrimaryTable table, uint16_t address);

void primary_table_write(PrimaryTable table, uint16_t address, uint16_t value);

#include "primary_table_private.h"

#endif //INJECTOR_PRIMARY_TABLE_H
