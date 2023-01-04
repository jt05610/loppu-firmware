/**
  ******************************************************************************
  * @file   coils.h
  * @author Jonathan Taylor
  * @date   04 Jan 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef PRESSSURESENSOR_COILS_H
#define PRESSSURESENSOR_COILS_H

#include "modbus.h"

void coils_create(PrimaryTable base, Device device);

#endif //PRESSSURESENSOR_COILS_H