/**
  ******************************************************************************
  * @file   coils.h
  * @author jtaylor
  * @date   21 Mar 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef NEEDLE_MOVER_COILS_H
#define NEEDLE_MOVER_COILS_H

#include "modbus.h"

void coils_create(PrimaryTable base, Device device);

#endif //NEEDLE_MOVER_COILS_H