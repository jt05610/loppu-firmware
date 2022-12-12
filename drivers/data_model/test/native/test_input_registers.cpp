//
// Created by taylojon on 11/23/2022.
//
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "data_model/input_registers.h"
}

uint8_t values[3];

uint16_t read_0()
{
    return values[0];
}

uint16_t read_1()
{
    return values[1];
}

uint16_t read_2()
{
    return values[2];
}

static ir_handler_t handlers[3] = {
        read_0,
        read_1,
        read_2
};

TEST_GROUP(input_registers)
{
    primary_table_t inputs;

    void setup()
    {
        values[0] = 0;
        values[1] = 0;
        values[2] = 0;
        input_registers_create(&inputs, handlers);
    }

    void teardown()
    {

    }

    void _test_read(uint16_t address, uint16_t expected)
    {
        uint16_t actual = primary_table_read(&inputs, address);
        LONGS_EQUAL(expected, actual);
    }
};

TEST(input_registers, reads)
{
    uint16_t     expected[] = {0xFF, 0xBE, 0xEF};
    for (uint8_t i          = 0; i < 3; i++)
    {
        values[i] = expected[i];
        _test_read(i, expected[i]);
    }
}