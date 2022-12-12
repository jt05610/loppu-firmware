/**
  ******************************************************************************
  * @file   comm_test_groups.h
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

#ifndef COMM_COMM_TEST_GROUPS_H
#define COMM_COMM_TEST_GROUPS_H

#include "CppUTest/CommandLineTestRunner.h"

IMPORT_TEST_GROUP(types);
IMPORT_TEST_GROUP(DataLink);
IMPORT_TEST_GROUP(ServerDataLink);
IMPORT_TEST_GROUP(util);
IMPORT_TEST_GROUP(EventLog);
IMPORT_TEST_GROUP(ServerApplication);

#endif //COMM_COMM_TEST_GROUPS_H
