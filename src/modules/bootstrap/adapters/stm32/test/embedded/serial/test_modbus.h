/**
  ******************************************************************************
  * @file   test_modbus.h
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_TEST_MODBUS_H
#define INJECTOR_TEST_MODBUS_H

#include "modbus.h"

void init_modbus_test();

void test_read_coil();

void test_read_di();

void test_read_hr();

void test_read_ir();

void test_write_coil();

void test_write_hr();

#endif //INJECTOR_TEST_MODBUS_H
