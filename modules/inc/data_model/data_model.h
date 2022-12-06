/**
  ******************************************************************************
  * @file   data_model.h
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

#ifndef INJECTOR_DATA_MODEL_H
#define INJECTOR_DATA_MODEL_H

#include "primary_table.h"

typedef struct data_model_t * DataModel;

typedef struct data_model_t
{
    PrimaryTable * tables;

} data_model_t;

void datamodel_create(DataModel base, PrimaryTable tables[4]);

uint16_t datamodel_read(DataModel base, uint32_t address);

uint16_t datamodel_write(DataModel base, uint32_t address, uint16_t value);

#endif //INJECTOR_DATA_MODEL_H