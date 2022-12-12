//
// Created by taylojon on 11/23/2022.
//

#include "CppUTest/TestHarness.h"


extern "C" {
#include "data_model/coils.h"
}

static struct FakeDevice {
    bool homing;
    bool going_to_target;
    bool stopping;
    bool nudging;
} fake_device;

bool *fake_device_states[4] = {
        &fake_device.homing,
        &fake_device.going_to_target,
        &fake_device.stopping,
        &fake_device.nudging
};
uint16_t
home(uint16_t value)
{
    if (value != 0xFF)
        fake_device.homing = value;
    return fake_device.homing;
}

uint16_t go_to_target(uint16_t value)
{
    if (value != 0xFF)
        fake_device.going_to_target = value;
    return fake_device.going_to_target;

}
uint16_t stop(uint16_t value)
{
    if (value != 0xFF)
        fake_device.stopping = value;
    return fake_device.stopping;

}
uint16_t nudge(uint16_t value)
{
    if (value != 0xFF)
        fake_device.nudging = value;
    return fake_device.nudging;
}

coils_handler_t handlers[] = {};

TEST_GROUP(coils)
{
    coils_t coils;

    void setup()
    {
        coils_create(&coils);
        fake_device = {0,0,0,0};
    }

    void teardown()
    {
    }

    void _test_read(uint16_t address, uint16_t expected)
    {
        uint16_t actual = coils_read(&coils, address);
        LONGS_EQUAL(expected, actual);
    }

    void _test_write(uint16_t address, uint16_t state)
    {
        coils_write(&coils, address, state);
        LONGS_EQUAL(*fake_device_states[address], state);
    }
};

TEST(coils, reads)
{
    for (uint8_t i = 0; i < 4; i ++)
        _test_read(i, 0);
}

TEST(coils, writes)
{
    for (uint8_t i = 0; i < 4; i ++)
        _test_write(i, 1);
}