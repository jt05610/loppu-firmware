/**
  ******************************************************************************
  * @file   posix_serialTest.cpp
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  Tests for posix_serial module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifdef __APPLE__

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "serial_spy.h"
#include "serial/posix_serial.h"
#include "timer/posix_timer.h"
}

TEST_GROUP(posix_serial)
{
    serial_t comm;
    const char * port = "/dev/cu.usbmodem1201";
    uint32_t      baud = 19200;
    sized_array_t read_array;
    uint8_t       rx_buffer[256];
    timer_t       time;

    void setup() override
    {
        read_array.size      = 12;
        serial_init_t params = {
                .port=port,
                .baud=baud,
                .rx_buffer = rx_buffer
        };

        posix_serial_create(&comm, &params);
        posix_timer_create(&time);
        posix_serial_set_timer(&time);
        serial_open(&comm);
    }

    void teardown() override
    {
        serial_close(&comm);
    }
};


TEST(posix_serial, read_and_write)
{
    timer_delay(&time, 1650);
    sized_array_t array;
    array.size = 8;
    uint8_t bytes[] = {
            0x00, 0x01, 0xfe, 0xed,
            0xbe, 0xef, 0xac, 0x2a
    };

    sized_array_create(bytes, array.size, &array);
    CHECK_TRUE(serial_write(&comm, &array));
    bool end = false;
    while (!end)
        end = serial_read(&comm, &read_array);
    if (read_array.size)
        for (size_t i = 0; i < 8; i++)
            LONGS_EQUAL(bytes[i], read_array.bytes[i]);
    else
        FAIL("couldn't read");
}


TEST(posix_serial, set_option)
{
    serial_set_options(&comm, SerialReadOnly);
    LONGS_EQUAL(SerialReadOnly, posix_serial_get_options());
}

TEST(posix_serial, list_ports)
{
    CommPortList list;
    list = serial_list_ports(&comm);
    CHECK_TRUE(list->n_ports);
    for (uint8_t i = 0; i < list->n_ports; i++)
    {
        CHECK_TRUE(strstr(list->ports[i]->name, list->ports[i]->device));
    }
}

#endif