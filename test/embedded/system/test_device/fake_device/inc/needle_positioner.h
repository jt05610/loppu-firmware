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

#include "peripherals.h"

typedef struct needle_positioner_t * NeedlePositioner;

NeedlePositioner
needle_positioner_create(Peripherals hal, void * uart_inst, void * tim_inst);

void needle_positioner_run(NeedlePositioner positioner);

#endif //NEEDLEPOSITIONER_NEEDLEPOSITIONER_H
