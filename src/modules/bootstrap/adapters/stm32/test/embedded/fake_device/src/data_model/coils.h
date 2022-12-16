/**
  ******************************************************************************
  * @file   coils.h
  * @author jtaylor
  * @date   12 Dec 2022
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef FAKEDEVICE_COILS_H
#define FAKEDEVICE_COILS_H

#include "modbus.h"

void coils_create(PrimaryTable base, void * device);

#endif //FAKEDEVICE_COILS_H