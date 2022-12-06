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

#include "data_model/data_model.h"



void
datamodel_create(DataModel base, PrimaryTable * tables)
{
    base->tables = tables;
}

uint16_t
datamodel_read(DataModel base, uint32_t address)
{
    uint32_t table = address / 10000;
    return primary_table_read(base->tables[table], address % 10000);
}

uint16_t
datamodel_write(DataModel base, uint32_t address, uint16_t value)
{

    uint32_t table = address / 10000;
    primary_table_write(base->tables[table], address % 10000, value);
    return value;
}
