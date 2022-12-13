/**
  ******************************************************************************
  * @file   timer_test_groups.h
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

#ifndef DRIVERS_TIMER_TEST_GROUPS_H
#define DRIVERS_TIMER_TEST_GROUPS_H

#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(FakePWM);
IMPORT_TEST_GROUP(PWM);
IMPORT_TEST_GROUP(FakeTimeService);
#ifdef WIN32
IMPORT_TEST_GROUP(win_timer);
#endif
IMPORT_TEST_GROUP(posix_timer);

#endif //DRIVERS_TIMER_TEST_GROUPS_H
