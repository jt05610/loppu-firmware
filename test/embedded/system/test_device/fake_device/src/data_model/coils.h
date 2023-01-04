/**
  ******************************************************************************
  * @file   coils.h
  * @author jtaylor
  * @date   03 Jan 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef FAKEDEVICE_COILS_H
#define FAKEDEVICE_COILS_H

#include "modbus.h"

void coils_create(PrimaryTable base, Device device);

#endif //FAKEDEVICE_COILS_H