/**
  ******************************************************************************
  * @file   serial_spy.h
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef MICROFLUIDICSYSTEM_SERIAL_SPY_H
#define MICROFLUIDICSYSTEM_SERIAL_SPY_H

#include "../../../../modbus/inc/public/modbus/project_types.h"

char * spy_path();

bool serial_spy_read(uint8_t * data, size_t n_char);

bool serial_spy_write(sized_array_t * data);

void serial_spy_clear();

#endif //MICROFLUIDICSYSTEM_SERIAL_SPY_H
