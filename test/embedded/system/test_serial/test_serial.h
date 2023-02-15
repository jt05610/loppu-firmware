/**
  ******************************************************************************
  * @file   test_serial.h
  * @author Jonathan Taylor
  * @date   2/15/23
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
#include "unity.h"

void test_open();
void test_close();
void test_read();
void test_write();
void test_flush();

void test_available();
void test_setTimeout();


#endif //INJECTOR_TEST_SERIAL_H
