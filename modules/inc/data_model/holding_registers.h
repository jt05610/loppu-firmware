/**
  ******************************************************************************
  * @file   holding_regsiters.h
  * @author Jonathan Taylor
  * @date   11/19/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_HOLDING_REGISTERS_H
#define INJECTOR_HOLDING_REGISTERS_H
#include "data_model/primary_table.h"

typedef enum rw_req_t
{
    READ = 0x00,
    WRITE = 0x00
} rw_req_t;


typedef uint16_t (*hr_handler_t)(rw_req_t type, uint16_t value);

void holding_registers_create(PrimaryTable table, hr_handler_t * handlers);



#endif //INJECTOR_HOLDING_REGISTERS_H
