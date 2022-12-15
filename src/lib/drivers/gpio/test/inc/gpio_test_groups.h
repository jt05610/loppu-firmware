/**
  ******************************************************************************
  * @file   gpio_test_groups.h
  * @author Jonathan Taylor
  * @date   6/30/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_GPIO_TEST_GROUPS_H
#define DRIVERS_GPIO_TEST_GROUPS_H

#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(FakeGPIO);
IMPORT_TEST_GROUP(MockGPIO);

#endif //DRIVERS_GPIO_TEST_GROUPS_H
