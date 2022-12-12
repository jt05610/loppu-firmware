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

#include "../inc/buttons.h"

void
buttons_create(Buttons self, uint32_t bit_mask, uint8_t n_buttons)
{
    self->state = 0;
    self->bit_mask = bit_mask;
    self->n_buttons = n_buttons;
}

void
buttons_handle(Buttons self, uint8_t state_flag)
{
    self->state |= (state_flag & self->bit_mask);
    self->state &= ~(state_flag >> self->n_buttons);
}

