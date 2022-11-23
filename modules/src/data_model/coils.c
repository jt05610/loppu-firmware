/**
  ******************************************************************************
  * @file   coils.c
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

#include "data_model/coils.h"

#define N_COILS 4


static coils_handler_t _handlers[N_COILS] = {
        home,
        go_to_target,
        stop,
        nudge
};

void
coils_create(Coils base)
{
    base->handlers = _handlers;
}

uint16_t
coils_read(Coils base, uint16_t address)
{
    return base->handlers[address](0xFF);
}

void
coils_write(Coils base, uint16_t address, uint16_t value)
{
    base->handlers[address](value);
}