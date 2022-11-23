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

typedef struct coils_t {
    coils_handler_t *handlers;
} CoilsStruct;

static coils_handler_t handlers[N_COILS] = {
        home,
        go_to_target,
        stop,
        nudge
};

void discrete_inputs_create(Coils base)
{
    base->handlers = handlers;
}

uint16_t discrete_inputs_handle(Coils base, uint16_t address)
{
    return base->handlers[address]();
}
