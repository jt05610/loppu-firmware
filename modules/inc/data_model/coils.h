/**
  ******************************************************************************
  * @file   coils.h
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

#ifndef INJECTOR_COILS_H
#define INJECTOR_COILS_H

#include <stdint-gcc.h>

typedef struct coils_t * Coils;

typedef uint16_t (* coils_handler_t)(uint16_t value);

void coils_create(Coils base);

uint16_t coils_read(Coils base, uint16_t address);

void coils_write(Coils base, uint16_t address, uint16_t value);

uint16_t home(uint16_t value);
uint16_t go_to_target(uint16_t value);
uint16_t stop(uint16_t value);
uint16_t nudge(uint16_t value);

#endif //INJECTOR_COILS_H
