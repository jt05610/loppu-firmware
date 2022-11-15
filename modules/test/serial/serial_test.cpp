/**
  ******************************************************************************
  * @file   serialTest.cpp
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  Tests for serial module.
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
#include "serial_spy.h"
#include "fake_serial.h"
#include "fcntl.h"
}

TEST_GROUP(serial)
{
    serial_t comm;
    const char * port = spy_path();
    uint32_t baud = 19200;
    uint8_t  rx_buffer[256];

    void setup() override
    {
        serial_init_t params = {
                .port=port,
                .baud=baud,
                .rx_buffer = rx_buffer
        };
        fake_serial_create(&comm, &params);
        serial_spy_clear();
    }

    void teardown() override
    {
        serial_close(&comm);
        serial_spy_clear();
    }
};

TEST(serial, Create)
{
    LONGS_EQUAL(baud, serial_get_baud(&comm));
}

TEST(serial, Open)
{
    serial_set_options(&comm, SerialReadOnly);
    CHECK_TRUE(serial_open(&comm));
}

TEST(serial, Close)
{
    serial_open(&comm);
    serial_close(&comm);
}

TEST(serial, Read)
{
    sized_array_t read;
    const char * data = "testing read";
    sized_array_t array;
    array.size  = strlen(data);
    array.bytes = (uint8_t *) data;
    serial_spy_write(&array);

    serial_set_options(&comm, SerialReadOnly);
    serial_open(&comm);
    serial_read(&comm, &read);
    for (size_t i = 0; i < array.size; i++)
        LONGS_EQUAL(data[i], read.bytes[i]);
}

TEST(serial, Write)
{
    sized_array_t array;
    const char * data = "testing write";
    sized_array_create((uint8_t *) data, strlen(data), &array);
    serial_set_options(&comm, SerialWriteOnly);
    serial_open(&comm);
    CHECK_TRUE(serial_write(&comm, &array));
    sized_array_t read_data;
    serial_read(&comm, &read_data);
    STRCMP_EQUAL(data, (char *) read_data.bytes);
}