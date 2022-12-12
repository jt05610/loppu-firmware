//
// Created by Jonathan Taylor on 4/28/22.
//

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "datalink_spy.h"
#include ".private/server_dl.h"
}

TEST_GROUP(ServerDataLink)
{
    datalink_t    server;
    const uint8_t myAddress = 0x03;
    modbus_pdu_t  main_pdu;
    uint8_t       rx_buffer[256];
    sized_array_t rx_array;

    void setup() override
    {
        server_dl_create(&server, myAddress, rx_buffer, &main_pdu, 0, 0);
    }

    void teardown() override
    {
    }

    void receiveMessage(SerialPDU data)
    {
        serialize_serial_pdu(data, &rx_array);
        for(uint8_t i = 0; i < rx_array.size; i ++)
            rx_buffer[i] = rx_array.bytes[i];
        server.target_pos = rx_array.size;
    }

    void receiveWrongAddress()
    {
        uint8_t      message[] = {0x12, 0x34};
        modbus_pdu_t mod_pdu;
        serial_pdu_t received;
        create_modbus_pdu(0x01, message, 2, &mod_pdu);
        dl_format_pdu(myAddress - 1, &mod_pdu, &received);
        receiveMessage(&received);
    }

    void receiveBroadcast()
    {
        uint8_t      message[] = {0x12, 0x34};
        modbus_pdu_t mod_pdu;
        serial_pdu_t received;
        create_modbus_pdu(0x01, message, 2, &mod_pdu);
        dl_format_pdu(0x00, &mod_pdu, &received);
        receiveMessage(&received);
    }

    void receiveUnicast()
    {
        uint8_t      message[] = {0x12, 0x34};
        modbus_pdu_t mod_pdu;
        serial_pdu_t received;
        create_modbus_pdu(0x01, message, 2, &mod_pdu);
        dl_format_pdu(myAddress, &mod_pdu, &received);
        receiveMessage(&received);

    }

    void receiveBadCRC()
    {
        modbus_pdu_t mod_pdu;
        serial_pdu_t received;
        received.pdu = &mod_pdu;
        uint8_t message[] = {0x12, 0x34};
        dl_spy_create_pdu(
                myAddress, 0x01, message, 2, 0x1234, &received
        );
        receiveMessage(&received);
    }
};

TEST(ServerDataLink, unicast)
{
    receiveUnicast();
    dl_update(&server);
    LONGS_EQUAL(1, server_dl_get_counter(BusMessageCount));
    LONGS_EQUAL(1, server_dl_get_counter(ServerMessageCount));
}

TEST(ServerDataLink, broadcast)
{
    receiveBroadcast();
    dl_update(&server);
    LONGS_EQUAL(1, server_dl_get_counter(BusMessageCount));
    LONGS_EQUAL(0, server_dl_get_counter(ServerMessageCount));
    LONGS_EQUAL(1, server_dl_get_counter(ServerNoResponseCount));
}

TEST(ServerDataLink, FrameCheckError)
{
    receiveBadCRC();
    dl_update(&server);
    LONGS_EQUAL(0, server_dl_get_counter(BusMessageCount));
    LONGS_EQUAL(1, server_dl_get_counter(BusCommunicationErrorCount));
}

TEST(ServerDataLink, WrongAddress)
{
    receiveWrongAddress();
    dl_update(&server);
    LONGS_EQUAL(1, server_dl_get_counter(BusMessageCount));
    LONGS_EQUAL(0, server_dl_get_counter(ServerMessageCount));
}