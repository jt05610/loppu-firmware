/**
  ******************************************************************************
  * @file   buttons.h
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

#ifndef INJECTOR_BUTTONS_H
#define INJECTOR_BUTTONS_H

#include <stdint-gcc.h>

typedef struct buttons_t * Buttons;
typedef struct buttons_interface_t * ButtonsInterface;

typedef void (*button_handler_t)();

void buttons_create(Buttons self, button_handler_t * handlers, uint8_t n_handlers);
void buttons_rising_handler(Buttons self, uint8_t button);
void buttons_falling_handler(Buttons self, uint8_t button);
void buttons_handle(Buttons self, uint8_t state_flag);
void buttons_update(Buttons self);

#include ".private/buttons_private.h"

#endif //INJECTOR_BUTTONS_H
