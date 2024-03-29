/**
  ******************************************************************************
  * @file   coils.h
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
#ifndef NEEDLEPOSITIONER_COILS_H
#define NEEDLEPOSITIONER_COILS_H

#include "../../../../modules/modbus/inc/modbus.h"

void coils_create(PrimaryTable base, void * device);

#endif //NEEDLEPOSITIONER_COILS_H