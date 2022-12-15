/**
  ******************************************************************************
  * @file   types.h
  * @author Jonathan Taylor
  * @date   6/23/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef MICROFLUIDICSYSTEM_TYPES_H
#define MICROFLUIDICSYSTEM_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "pdu_types.h"
#include "func_codes.h"

typedef void (* restart_func_t)(void *);

typedef void (*write_handler_t) (void * serial_obj, uint8_t * bytes, uint16_t n);

#endif //MICROFLUIDICSYSTEM_TYPES_H
