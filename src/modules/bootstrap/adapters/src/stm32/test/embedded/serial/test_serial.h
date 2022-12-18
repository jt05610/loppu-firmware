/**
  ******************************************************************************
  * @file   serial_test.h
  * @author Jonathan Taylor
  * @date   12/14/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_TEST_SERIAL_H
#define INJECTOR_TEST_SERIAL_H

#include "stm32g0xx/stm32_serial.h"

void set_serial_test_instance(Serial serial);

void test_read();

void test_write();

#endif //INJECTOR_TEST_SERIAL_H
