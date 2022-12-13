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

#include "modbus/primary_table.h"
#include "modbus/pdu_types.h"

#define DI_TABLE 0x00
#define COIL_TABLE 0x01
#define IR_TABLE 0x02
#define HR_TABLE 0x03

typedef struct data_model_t * DataModel;

typedef struct data_model_t
{
    void * device;
    primary_table_t * tables;
} data_model_t;

DataModel datamodel_create(PrimaryTable tables);

void datamodel_handle(DataModel base, ModbusPDU pdu);

#endif //INJECTOR_DATA_MODEL_H