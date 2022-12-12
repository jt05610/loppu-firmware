/**
  ******************************************************************************
  * @file   serial_spyTest.cpp
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  Tests for serial_spy module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <cstring>
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "serial_spy.h"
}

TEST_GROUP(serial_spy)
{
    void setup() override
    {
    }

    void teardown() override
    {
        serial_spy_clear();
    }
};

TEST(serial_spy, write)
{
    const char * data = "1234";
    sized_array_t array;
    array.size  = strlen(data);
    array.bytes = (uint8_t *) data;
    serial_spy_write(&array);
    auto read_data = (uint8_t *) calloc(strlen(data), sizeof(uint8_t));
    serial_spy_read(read_data, strlen(data));
    STRCMP_EQUAL(data, (char *) read_data);
}

TEST(serial_spy, clear)
{
    const char * data = "1234";
    sized_array_t array;
    array.size  = strlen(data);
    array.bytes = (uint8_t *) data;
    serial_spy_write(&array);
    serial_spy_clear();
    auto read_data = (uint8_t *) calloc(strlen(data), sizeof(uint8_t));
    serial_spy_read(read_data, strlen(data));
    STRCMP_EQUAL("", (char *) read_data);
}