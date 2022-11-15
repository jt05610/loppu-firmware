/**
  ******************************************************************************
  * @file   win_serialTest.cpp
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  Tests for win_serial module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifdef _WIN32
#include "CppUTest/TestHarness.h"

#define BUFF_SIZE 256
extern "C"
{
#include "serial/win_serial.h"
#include <cstring>
}

TEST_GROUP(win_serial)
{
    serial_t comm;
    uint32_t      baud        = 9600;
    uint8_t rx_buffer[BUFF_SIZE];
    const char * port = R"(\\.\COM3)";

    serial_init_t init;

    void setup() override
    {
        init.port = port;
        init.baud = baud;
        init.rx_buffer = rx_buffer;
        win_serial_create(&comm, &init);
    }

    void teardown() override
    {
        serial_close(&comm);
    }
};

TEST(win_serial, create)
{
    LONGS_EQUAL(baud, serial_get_baud(&comm));
}

TEST(win_serial, list_ports)
{
    CommPortList ports = serial_list_ports(&comm);
    STRCMP_EQUAL("\\Device\\USBSER000", ports->ports[0]->device);
    CHECK_TRUE(ports->n_ports > 0);
    while(ports->n_ports--)
        free(ports->ports[ports->n_ports]);
    free(ports);
}

TEST(win_serial, open)
{
    CHECK_TRUE(serial_open(&comm));
}

TEST(win_serial, read_write)
{
    const char * msg = "test message";
    sized_array_t to_send;
    sized_array_t to_read;
    uint8_t buff[256];
    for (to_send.size = 0; to_send.size < strlen(msg); to_send.size ++)
        buff[to_send.size] = msg[to_send.size];
    buff[to_send.size++] = '\n';
    buff[to_send.size] = '\0';
    to_send.bytes = buff;
    serial_open(&comm);
    CHECK_TRUE(serial_write(&comm, &to_send));
    serial_read(&comm, &to_read);
    for (size_t i = 0; i < to_send.size - 1; i ++)
        LONGS_EQUAL(to_send.bytes[i], to_read.bytes[i]);
    serial_read(&comm, &to_read);
    LONGS_EQUAL(0, to_read.size);
}

#endif