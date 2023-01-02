/**
  ******************************************************************************
  * @file   holding_registers.h
  * @author Jonathan Taylor
  * @date   11 Dec 2022
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef NEEDLEPOSITIONER_HOLDING_REGISTERS_H
#define NEEDLEPOSITIONER_HOLDING_REGISTERS_H

#include "modbus/primary_table.h"

void holding_registers_create(PrimaryTable base);

#endif //NEEDLEPOSITIONER_HOLDING_REGISTERS_H