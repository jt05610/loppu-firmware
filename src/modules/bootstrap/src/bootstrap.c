/**
  ******************************************************************************
  * @file   bootstrap.c
  * @author Jonathan Taylor
  * @date   12/11/22
  * @brief  Source for bootstrap
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <stddef.h>
#include "bootstrap.h"

Peripherals
bootstrap(adapter_t adapter, void * params)
{
    if (adapter)
        return adapter(params);
    return NULL;
}
