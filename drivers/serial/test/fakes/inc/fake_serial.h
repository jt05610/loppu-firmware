/**
  ******************************************************************************
  * @file   FakeSerial.h
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef MICROFLUIDICSYSTEM_FAKE_SERIAL_H
#define MICROFLUIDICSYSTEM_FAKE_SERIAL_H

#include "../../../inc/serial.h"

void fake_serial_create(Serial base, SerialInit params);

#endif //MICROFLUIDICSYSTEM_FAKE_SERIAL_H
