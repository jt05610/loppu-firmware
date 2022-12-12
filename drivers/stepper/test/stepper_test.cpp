/**
  ******************************************************************************
  * @file   stepperTest.cpp
  * @author Jonathan Taylor
  * @date   7/11/22
  * @brief  Tests for stepper module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "fake_stepper.h"

}

TEST_GROUP(stepper)
{
    stepper_t        stepper;

    void setup() override
    {
    }

    void teardown() override
    {
    }
};
