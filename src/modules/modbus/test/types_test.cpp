/**
  ******************************************************************************
  * @file   types_test.cpp
  * @author Jonathan Taylor
  * @date   7/5/22
  * @brief  Tests for types module.
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
#include ".private/types.h"
}

TEST_GROUP(types)
{
    uint16_t start;
    uint16_t target;
    serial_pdu_t pdu;
    uint8_t pdu_buffer[RX_BUFFER_SIZE];
    uint8_t rx_buffer[RX_BUFFER_SIZE];

    void setup() override
    {
        pdu.pdu = (ModbusPDU) calloc(1, sizeof(modbus_pdu_t));
        pdu.pdu->data.bytes = pdu_buffer;
        pdu.pdu->data.size = 0;
        start = 0;
        target = 0;
    }
    void teardown() override
    {
        free(pdu.pdu);
    }
    void set_buffer(uint8_t * buffer, const uint16_t size, const uint16_t begin)
    {
        uint16_t go_to = begin + size;
        uint16_t remaining = 0;
        if (go_to > RX_BUFFER_SIZE) {
            remaining = go_to - RX_BUFFER_SIZE;
            go_to = RX_BUFFER_SIZE;
        }
        for (uint16_t i = begin; i < go_to; i ++)
            rx_buffer[i] = buffer[i - begin];
        if (remaining) {
            set_buffer(&buffer[size - remaining], remaining, 0);
        }
    }

    void test_extract(uint16_t from) {
        const uint16_t size = 8;
        uint8_t msg[size] = {0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0xED, 0xFE};
        set_buffer(msg, size, from);
        start = extract_pdu(rx_buffer, from, size, &pdu);
        uint16_t expected_new_start = from + size;
        if (expected_new_start >= RX_BUFFER_SIZE)
            expected_new_start -= RX_BUFFER_SIZE;
        CHECK_EQUAL(expected_new_start, start);
        CHECK_EQUAL(0x01, pdu.address);
        CHECK_EQUAL(0x01, pdu.pdu->func_code);
        CHECK_EQUAL(0x04, pdu.pdu->data.size);
        CHECK_EQUAL(0xFEED, pdu.crc);
    }
};

TEST(types, extract_full_buffer)
{
    for(uint16_t i = 0; i < RX_BUFFER_SIZE; i ++)
        test_extract(i);
}

TEST(types, create_sized_array)
{
    const uint8_t data_size       = 4;
    uint8_t       data[data_size] = {'a', 'b', 'c', 'd'};
    sized_array_t array;
    sized_array_create(data, data_size, &array);
    LONGS_EQUAL(data_size, array.size);
    for (uint8_t i = 0; i < data_size; i++)
        LONGS_EQUAL(data[i], array.bytes[i]);
}

TEST(types, create_modbus_pdu)
{
    modbus_pdu_t  pdu;
    const uint8_t data_size       = 4;
    uint8_t       data[data_size] = {'a', 'b', 'c', 'd'};
    create_modbus_pdu(READ_COILS, data, data_size, &pdu);
    LONGS_EQUAL(READ_COILS, pdu.func_code);
    for (uint8_t i = 0; i < data_size; i++)
        LONGS_EQUAL(data[i], pdu.data.bytes[i]);
}

TEST(types, create_serial_pdu)
{
    serial_pdu_t  pdu;
    const uint8_t data_size = 4;

    uint8_t      data[data_size + 3] = {'a', 'b', 'c', 'd'};
    modbus_pdu_t modbus_pdu;
    create_modbus_pdu(READ_COILS, data, data_size, &modbus_pdu);
    create_serial_pdu(0x00, &modbus_pdu, 0xFFFF, &pdu);
    LONGS_EQUAL(0xFFFF, pdu.crc);
    LONGS_EQUAL(0x00, pdu.address);
    LONGS_EQUAL(READ_COILS, pdu.pdu->func_code);
    LONGS_EQUAL(data_size, pdu.pdu->data.size);
    for (uint8_t i = 0; i < data_size; i++)
        LONGS_EQUAL(data[i], pdu.pdu->data.bytes[i]);
}

TEST(types, flatten_modbus_pdu)
{
    modbus_pdu_t  modbus_pdu;
    sized_array_t actual;

    const uint8_t data_size           = 4;
    uint8_t       data[data_size + 1] = {'a', 'b', 'c', 'd'};
    create_modbus_pdu(READ_COILS, data, data_size, &modbus_pdu);
    uint8_t expected[data_size + 1] = {
            READ_COILS, data[0], data[1], data[2], data[3],
    };
    serialize_modbus_pdu(&modbus_pdu, &actual);
    for (uint8_t i = 0; i < data_size + 1; i++)
        LONGS_EQUAL(expected[i], actual.bytes[i]);
}

TEST(types, flatten_serial_pdu)
{
    modbus_pdu_t  modbus_pdu;
    serial_pdu_t  serial_pdu;
    sized_array_t actual;

    const uint8_t data_size           = 4;
    uint8_t       data[data_size + 4] = {'a', 'b', 'c', 'd'};
    create_modbus_pdu(READ_COILS, data, data_size, &modbus_pdu);
    create_serial_pdu(0x00, &modbus_pdu, 0xFFFF, &serial_pdu);
    uint8_t expected[data_size + 4] = {
            0x00, READ_COILS, data[0], data[1], data[2], data[3], 0xFF, 0xFF
    };
    serialize_serial_pdu(&serial_pdu, &actual);
    for (uint8_t i = 0; i < data_size + 4; i++)
        LONGS_EQUAL(expected[i], actual.bytes[i]);
}

TEST(types, deserialize_serial_pdu)
{
    modbus_pdu_t  modbus_pdu;
    serial_pdu_t  expected_pdu;
    sized_array_t actual;
    modbus_pdu_t  actual_mod_pdu;
    serial_pdu_t  actual_pdu          = {.address = 0, .pdu = &actual_mod_pdu, .crc = 0};
    const uint8_t data_size           = 4;
    uint8_t       data[data_size + 4] = {'a', 'b', 'c', 'd'};
    create_modbus_pdu(READ_COILS, data, data_size, &modbus_pdu);
    create_serial_pdu(0x00, &modbus_pdu, 0xFFFF, &expected_pdu);

    serialize_serial_pdu(&expected_pdu, &actual);
    deserialize_pdu(&actual, &actual_pdu);
    modbus_pdu.data.bytes += 2;
    CHECK_TRUE(equal_serial_pdu(&expected_pdu, &actual_pdu));
}