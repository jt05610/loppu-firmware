/**
  ******************************************************************************
  * @file   test_groups.h
  * @author Jonathan Taylor
  * @date   6/29/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_TEST_GROUPS_H
#define DRIVERS_TEST_GROUPS_H

#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(serial);
IMPORT_TEST_GROUP(serial_spy);
#ifdef _WIN32
IMPORT_TEST_GROUP(win_serial);
#else
IMPORT_TEST_GROUP(posix_serial);
#endif

#endif //DRIVERS_TEST_GROUPS_H
