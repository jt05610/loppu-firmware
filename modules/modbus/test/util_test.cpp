//
// Created by Jonathan Taylor on 5/19/22.
//

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "public/modbus/util.h"
}

TEST_GROUP(util)
{
    static const uint8_t len = 4;

    void setup() override
    {

    }

    void teardown() override
    {

    }
};

TEST(util, uint8_to_uint16)
{
    const uint8_t bytes[len] = {0x00, 0x12, 0x34, 0x56};
    LONGS_EQUAL(0x0012, UINT8_TO_UINT16(bytes, 0));
    LONGS_EQUAL(0x1234, UINT8_TO_UINT16(bytes, 1));
    LONGS_EQUAL(0x3456, UINT8_TO_UINT16(bytes, 2));
}

TEST(util, uint16_to_uint8)
{
    const uint8_t bytes[len]     = {0x00, 0x12, 0x34, 0x56};
    uint8_t       byteArray[len] = {};
    uint16_t      value1         = 0x0012;
    uint16_t      value2         = 0x3456;
    UINT16_TO_UINT8_ARRAY(byteArray, 0, value1)
    UINT16_TO_UINT8_ARRAY(byteArray, 2, value2)
    for (uint8_t i = 0; i < len; i++)
        LONGS_EQUAL(bytes[i], byteArray[i]);
}

TEST(util, str_combine)
{
    const char * str_1 = "Bob ";
    const char * str_2 = "Dobalina";
    const char * title = "Mr. ";
    STRCMP_EQUAL("Mr. Bob Dobalina",
                 str_combine(title, (str_combine(str_1, str_2))));
}

TEST(util, uint8_to_uint32)
{
    const uint8_t bytes[4] = {0xFE, 0xED, 0xBE, 0xEF};
    LONGS_EQUAL(0xFEEDBEEF, UINT8_TO_UINT32(bytes, 0));
}


TEST(util, uint16_to_uint32)
{
    const uint16_t bytes[2] = {0xFEED, 0xBEEF};
    LONGS_EQUAL(0xFEEDBEEF, UINT16_TO_UINT32(bytes, 0));
}

TEST(util, uint32_to_uint16)
{
    uint32_t       value       = 0xFEEDBEEF;
    const uint16_t expected[2] = {0xFEED, 0xBEEF};
    uint16_t       actual[2];
    UINT32_TO_UINT16_ARRAY(actual, 0, value)

    LONGS_EQUAL(expected[0], actual[0]);
    LONGS_EQUAL(expected[1], actual[1]);
}

TEST(util, n_bytes)
{
    uint16_t quantity = 7;
    LONGS_EQUAL(1, BYTE_COUNT(quantity));
    quantity++;
    LONGS_EQUAL(1, BYTE_COUNT(quantity));
    quantity++;
    LONGS_EQUAL(2, BYTE_COUNT(quantity));
    quantity = 16;
    LONGS_EQUAL(2, BYTE_COUNT(quantity));
}


TEST(util, byte_from_bits)
{
    const uint8_t n       = 5;
    uint8_t       bits[n] = {1, 1, 1, 1, 1};
    uint8_t       result  = build_byte(bits, n);
    LONGS_EQUAL(31, result);
}
