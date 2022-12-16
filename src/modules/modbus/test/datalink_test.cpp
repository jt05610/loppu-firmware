//
// Created by Jonathan Taylor on 5/19/22.
//
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "datalink_spy.h"
}

TEST_GROUP(DataLink)
{
    datalink_t spy;

    void setup() override
    {
        dl_spy_create(&spy,  0x03);
    }

    void teardown() override
    {
    }
};

TEST(DataLink, FormatPDU)
{
    serial_pdu_t expected;
    serial_pdu_t actual;
    modbus_pdu_t pdu;
    modbus_pdu_t expected_mod_pdu;
    expected.pdu = &expected_mod_pdu;
    uint8_t data[2] = {0x12, 0x34};
    create_modbus_pdu(0x01, data, 2, &pdu);
    dl_spy_create_pdu(
            0x03,
            0x01,
            data,
            2,
            0xD75C,
            &expected
    );

    dl_format_pdu(0x03, &pdu, &actual);
    CHECK_TRUE(equal_serial_pdu(&expected, &actual));
}

TEST(DataLink, HappyCRCCheck)
{
    serial_pdu_t expected;
    modbus_pdu_t expected_mod_pdu;
    expected.pdu = &expected_mod_pdu;
    uint8_t data[] = {0x12, 0x34};
    dl_spy_create_pdu(
            0x03,
            0x01,
            data,
            2,
            0xD75C,
            &expected
    );
    CHECK_TRUE(dl_crc_check(&expected));
}

TEST(DataLink, SadCRCCheck)
{
    serial_pdu_t expected;
    modbus_pdu_t expected_mod_pdu;
    expected.pdu = &expected_mod_pdu;
    uint8_t data[] = {0x12, 0x34};
    dl_spy_create_pdu(
            0x03,
            0x01,
            data,
            2,
            0xD75D,
            &expected
    );

    CHECK_FALSE(dl_crc_check(&expected));
}

TEST(DataLink, HandleError)
{
    dl_handle_error(&spy);
    LONGS_EQUAL(1, dl_spy_error_count());
}