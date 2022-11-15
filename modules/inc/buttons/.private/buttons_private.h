/**
  ******************************************************************************
  * @file   buttons_private.h
  * @author Jonathan Taylor
  * @date   11/14/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_BUTTONS_PRIVATE_H
#define INJECTOR_BUTTONS_PRIVATE_H

#include "buttons/buttons.h"

typedef struct buttons_t
{
    uint8_t state;
    volatile uint8_t update_flag;
    button_handler_t * handlers;
    uint8_t n_handlers;
} buttons_t;


#endif //INJECTOR_BUTTONS_PRIVATE_H
