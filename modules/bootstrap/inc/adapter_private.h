/**
  ******************************************************************************
  * @file   adapter_private.h
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_ADAPTER_PRIVATE_H
#define INJECTOR_ADAPTER_PRIVATE_H

#ifndef INJECTOR_ADAPTER_H
#include "adapter.h"
#endif

typedef struct adapter_t
{
    Serial serial;
    GPIO gpio;
    Timer timer;
} adapter_t;

#endif //INJECTOR_ADAPTER_PRIVATE_H
