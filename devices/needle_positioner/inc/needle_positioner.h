/**
  ******************************************************************************
  * @file   needle_positioner.h
  * @author Jonathan Taylor
  * @date   11 Dec 2022
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef NEEDLEPOSITIONER_NEEDLEPOSITIONER_H
#define NEEDLEPOSITIONER_NEEDLEPOSITIONER_H

#include "serial.h"
#include "gpio.h"

typedef struct needle_positioner_t * NeedlePositioner;

typedef struct needle_positioner_init_t {
    Serial serial;
    GPIO gpio;
} needle_positioner_init_t;

NeedlePositioner needle_positioner_create(needle_positioner_init_t * params);

void needle_positioner_run(NeedlePositioner positioner);

void bootstap(needle_positioner_init_t * params);

#endif //NEEDLEPOSITIONER_NEEDLEPOSITIONER_H
