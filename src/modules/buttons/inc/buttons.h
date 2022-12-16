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

#ifdef STM32G0
#include <stdint-gcc.h>
#else
#include <stdint.h>
#endif

typedef struct buttons_t * Buttons;

void buttons_create(Buttons self, uint32_t bit_mask, uint8_t n_buttons);
void buttons_handle(Buttons self, uint8_t state_flag);

#include ".private/buttons_private.h"

#endif //INJECTOR_BUTTONS_H
