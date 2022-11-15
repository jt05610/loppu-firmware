/**
  ******************************************************************************
  * @file   buttons.c
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

#include "buttons.h"

void
buttons_create(Buttons self, button_handler_t * handlers, uint8_t n_handlers)
{
    self->state = 0;
    self->handlers = handlers;
    self->n_handlers = n_handlers;
    self->update_flag = 0;
}

void
buttons_rising_handler(Buttons self, uint8_t button)
{
    self->state |= (0x01 << button);
}

void
buttons_falling_handler(Buttons self, uint8_t button)
{
    self->state &= ~(0x01 << button);
}

void
buttons_handle(Buttons self, uint8_t state_flag)
{
    self->update_flag = state_flag;
}

void
buttons_update(Buttons self)
{
    if (self->update_flag)
        self->handlers[self->update_flag]();
}
