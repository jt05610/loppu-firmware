//
// Created by Jonathan Taylor on 5/26/22.
//

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "datalink_spy.h"
#include "modbus.h"
#include "public/modbus/util.h"
#include "fake_device.h"
}

uint8_t       hasRestarted = 0;
sized_array_t read_array;

void fakeRestart(void *)
{
    hasRestarted = 1;
}

void
write_handler(void * serial_obj, uint8_t * bytes, uint16_t n)
{
    (void) serial_obj;
    read_array.bytes = bytes;
    read_array.size  = n;
}

TEST_GROUP(ServerApplication)
{
    ServerApp     server;
    fake_device_t fake_device;
    uint8_t       rx_buffer[256];
    uint8_t       fake_write_bytes[256];
    modbus_pdu_t  write_pdu;
    serial_pdu_t  write_ser_pdu;
    sized_array_t write_array;
    serial_pdu_t  expected_response;
    serial_pdu_t  actual_response;
    modbus_pdu_t  expected_mod_pdu;
    modbus_pdu_t  actual_mod_pdu;
    uint8_t       req_bytes[256];
    uint8_t       resp_bytes[256];

    static const uint8_t serverAddress = 0x01;

    void setup() override
    {
        write_pdu         = {0};
        write_ser_pdu     = {0};
        expected_response = {0};
        expected_mod_pdu  = {0};
        actual_response   = {0};
        actual_mod_pdu    = {0};
        actual_response.pdu = &actual_mod_pdu;
        fake_device_create(&fake_device);
        app_init_t app_params = {
                .address = serverAddress,
                .rx_buffer=rx_buffer,
                .serial_device = 0,
                .write_handler = write_handler,
                .restart = fakeRestart,
        };
        server = server_create(&app_params);
        server_attach_device(server, &fake_device, fake_device_get_tables());
    }

    void teardown() override
    {
        hasRestarted = 0;
    }

    void receiveMessage()
    {
        for (uint8_t i = 0; i < write_array.size; i++)
        {
            rx_buffer[i] = write_array.bytes[i];
        }
        server_new_data_handler(write_array.size);
    }

    void set_read(uint8_t addr)
    {
        dl_format_pdu(addr, &write_pdu, &write_ser_pdu);
        serialize_serial_pdu(&write_ser_pdu, &write_array);
        receiveMessage();
        deserialize_pdu(&write_array, &write_ser_pdu);
    }

    void expect(
            uint8_t address,
            uint8_t funcCode,
            uint8_t size
    )
    {
        create_modbus_pdu(funcCode, resp_bytes, size, &expected_mod_pdu);
        dl_format_pdu(address, &expected_mod_pdu, &expected_response);
    }

    void test_read(
            uint8_t table,
            uint8_t func_code,
            uint16_t start,
            uint16_t quantity,
            std::initializer_list<uint8_t> data
    )
    {
        resp_bytes[0]   = data.size();
        sized_array_t array;
        uint8_t       i = 0;
        for (auto     elem: data)
        {
            fake_write_bytes[i] = elem;
            resp_bytes[i + 1]   = elem;
            i++;
        }
        array.size  = data.size();
        array.bytes = fake_write_bytes;
        uint16_t value;
        if (table > COIL_TABLE)
        {
            value = UINT8_TO_UINT16(array.bytes, 0);
        } else
        {
            value = array.bytes[0];
        }
        fake_device_set_value(&fake_device, table, value);
        UINT16_TO_UINT8_ARRAY(req_bytes, 0, start)
        UINT16_TO_UINT8_ARRAY(req_bytes, 2, quantity)
        create_modbus_pdu(func_code, req_bytes, 4, &write_pdu);
        set_read(serverAddress);
        expect(
                serverAddress, func_code, data.size() + 1
        );
        server_update(server);
        check();
    }

    void test_write(
            uint8_t table,
            uint8_t func_code,
            uint16_t start,
            uint16_t quantity
    )
    {
        UINT16_TO_UINT8_ARRAY(req_bytes, 0, start)
        UINT16_TO_UINT8_ARRAY(req_bytes, 2, quantity)
        UINT16_TO_UINT8_ARRAY(resp_bytes, 2, quantity)
        create_modbus_pdu(func_code, req_bytes, 4, &write_pdu);
        set_read(serverAddress);

        expect(
                serverAddress, func_code, 4
        );
        server_update(server);
        uint16_t actual_value = fake_device_get_value(&fake_device, table);
        if (table < IR_TABLE)
        {
            quantity = quantity >> 15;
        }
        CHECK_EQUAL(quantity, actual_value);
        check();
    }

    void check()
    {
        deserialize_pdu(&read_array, &actual_response);
        CHECK_TRUE(equal_serial_pdu(&expected_response, &actual_response));
    }

#if 0
    void test_write(uint8_t func_code, uint16_t start, uint16_t value)
    {
        UINT16_TO_UINT8_ARRAY(req_bytes, 0, start)
        UINT16_TO_UINT8_ARRAY(req_bytes, 2, value)
        create_modbus_pdu(func_code, req_bytes, 4, &write_pdu);
        for (size_t i = 0; i < 4; i++)
            resp_bytes[i] = req_bytes[i];
        set_read(serverAddress);
        expect(serverAddress, func_code, 4);
        app_update(&server);
        check();
    }


    void test_write(
            uint8_t func_code,
            uint16_t start,
            uint16_t quantity,
            std::initializer_list<uint8_t> data
    )
    {
        UINT16_TO_UINT8_ARRAY(req_bytes, 0, start)
        UINT16_TO_UINT8_ARRAY(req_bytes, 2, quantity)
        UINT16_TO_UINT8_ARRAY(resp_bytes, 0, start)
        UINT16_TO_UINT8_ARRAY(resp_bytes, 2, quantity)
        req_bytes[4] = data.size();
        uint8_t   i  = 0;
        for (auto elem: data)
            req_bytes[5 + i++] = elem;
        create_modbus_pdu(func_code, req_bytes, 5 + data.size(), &write_pdu);
        set_read(serverAddress);
        expect(serverAddress, func_code, 4);
        app_update(&server);
        check();
    }

    void test_diag(
            uint8_t func_code,
            uint16_t sub_func,
            std::initializer_list<uint8_t> resp
    )
    {
        uint8_t * ptr = resp_bytes;
        size_t size      = 0;
        size_t resp_size = resp.size();
        if (DIAGNOSTICS == func_code)
        {
            resp_size += 2;
            size = 2 + resp.size();
            UINT16_TO_UINT8_ARRAY(req_bytes, 0, sub_func)
            UINT16_TO_UINT8_ARRAY(resp_bytes, 0, sub_func)
            ptr = &resp_bytes[2];
        }
        uint8_t * req_ptr = &req_bytes[2];
        for (auto elem: resp)
        {
            *ptr++     = elem;
            *req_ptr++ = elem;
        }
        create_modbus_pdu(func_code, req_bytes, size, &write_pdu);
        set_read(serverAddress);
        expect(serverAddress, func_code, resp_size);
        app_update(&server);
        check();
    }



    void testCounter(dl_counter_t counter, uint16_t value)
    {
        auto data     = (uint8_t *) calloc(4, sizeof(uint8_t));
        auto expected = (uint8_t *) calloc(4, sizeof(uint8_t));
        data[1]     = counter;
        expected[1] = counter;
        UINT16_TO_UINT8_ARRAY(expected, 2, value)
        expectResponse(serverAddress, DIAGNOSTICS, expected, 4);
        setRead(readPDU, serverAddress, DIAGNOSTICS, data, 4);
        app_update(client);
        check();
    }

    void expectResponse(
            uint8_t address,
            uint8_t funcCode,
            std::initializer_list<uint8_t> data
    )
    {
        uint8_t resp[data.size() + 1];
        uint8_t i = 0;
        resp[i++]     = data.size();
        for (auto elem: data)
            resp[i++] = elem;
        ModbusPDU tx_pdu = createPdu(funcCode, resp, data.size() + 1);
        expectedResponse = dl_format_pdu(address, tx_pdu);

    }


    void testMaskWrite(
            uint8_t funcCode,
            uint16_t startAddress,
            uint16_t andMask,
            uint16_t orMask
    )
    {
        uint8_t requestBytes[6];
        UINT16_TO_UINT8_ARRAY(requestBytes, 0, startAddress)
        UINT16_TO_UINT8_ARRAY(requestBytes, 2, andMask)
        UINT16_TO_UINT8_ARRAY(requestBytes, 4, orMask)
        setRead(readPDU, serverAddress, funcCode, requestBytes, 6);
        expectResponse(serverAddress, funcCode, requestBytes, 6);
        app_update(client);
        check();
    }

    void testReadWrite(
            table_t table,
            uint8_t funcCode,
            uint16_t readStart,
            uint16_t readQuantity,
            uint16_t writeStart,
            uint16_t writeQuantity,
            std::initializer_list<uint8_t> data,
            std::initializer_list<uint8_t> read_list
    )
    {
        uint8_t   dataBytes[read_list.size()];
        uint8_t   i = 0;
        for (auto elem: read_list)
            dataBytes[i++] = elem;
        fake_dm_write(
                model, table, readStart, readQuantity, dataBytes,
                read_list.size());
        uint8_t requestBytes[9 + data.size()];
        UINT16_TO_UINT8_ARRAY(requestBytes, 0, readStart)
        UINT16_TO_UINT8_ARRAY(requestBytes, 2, readQuantity)
        UINT16_TO_UINT8_ARRAY(requestBytes, 4, writeStart)
        UINT16_TO_UINT8_ARRAY(requestBytes, 6, writeQuantity)
        requestBytes[8] = data.size();
        i = 9;
        for (auto elem: data)
            requestBytes[i++] = elem;
        setRead(
                readPDU, serverAddress, funcCode, requestBytes,
                9 + data.size());
        expectResponse(serverAddress, funcCode, read_list);
        app_update(client);
        check();
    }
#endif
};

TEST(ServerApplication, ReadCoils)
{
    test_read(
            COIL_TABLE, READ_COILS,
            0x000, 0x0001,
            {0x01}
    );
}

TEST(ServerApplication, ReadDiscreteInputs)
{
    test_read(
            DI_TABLE, READ_DISCRETE_INPUTS,
            0x000, 0x0001,
            {0x01}
    );
}


TEST(ServerApplication, ReadHoldingRegisters)
{
    test_read(
            HR_TABLE, READ_HOLDING_REGISTERS,
            0x0000, 0x0001,
            {0xFE, 0xED}
    );
}

TEST(ServerApplication, ReadInputRegisters)
{
    test_read(
            IR_TABLE, READ_INPUT_REGISTERS,
            0x0000, 0x0001,
            {0xBE, 0xEF}
    );
}

TEST(ServerApplication, WriteSingleCoil)
{
    test_write(
            COIL_TABLE,
            WRITE_SINGLE_COIL,
            0x0000,
            0xFF00
    );
}

TEST(ServerApplication, WriteSingleRegister)
{
    test_write(
            HR_TABLE,
            WRITE_SINGLE_REGISTER,
            0x0000,
            0xFADE
    );
}

#if 0
TEST(ServerApplication, ReadExceptionStatus)
{
    uint8_t      set_reg[] = {0, 2, 3, 5, 6};
    for (uint8_t reg: set_reg)
        server_dl_set_exception_status(
                1, reg
        );
    test_diag(READ_EXCEPTION_STATUS, 0, {0x6D});
}

TEST(ServerApplication, DiagnosticsReturnQueryData)
{
    test_diag(
            DIAGNOSTICS, RETURN_QUERY_DATA,
            {0x12, 0x34, 0x56, 0x78}
    );
}


TEST(ServerApplication, WriteMultipleCoils)
{
    test_write(
            WRITE_MULTIPLE_COILS,
            0x0013, 0x000A,
            {0xCD, 0x01}
    );
}

TEST(ServerApplication, WriteMultipleRegisters)
{
    test_write(
            WRITE_MULTIPLE_REGISTERS,
            0x0001, 0x0002,
            {0x00, 0x0A, 0x01, 0x02}
    );
    sized_array_t to_send;
    serialize_serial_pdu(&write_ser_pdu, &to_send);
    printf("\n");
    for (uint16_t i = 0; i < to_send.size; i++)
        printf("%#04x,", to_send.bytes[i]);
    printf("\n");
}

#if 0
TEST(ServerApplication, DiagnosticsRestartCommunicationsDontClear)
{
    LONGS_EQUAL(0, hasRestarted);
    uint8_t  data[]      = {0x00, 0x00};
    uint8_t  request[4];
    uint16_t subFunction = RESTART_COMMUNICATIONS_OPTION;
    UINT16_TO_UINT8_ARRAY(request, 0, subFunction)
    for (uint8_t i = 0; i < 2; i++)
    {
        request[2 + i] = data[i];
    }
    expectResponse(serverAddress, DIAGNOSTICS, request, 4);
    setRead(readPDU, serverAddress, DIAGNOSTICS, request, 4);
    app_update(client);
    check();
    LONGS_EQUAL(1, hasRestarted);
}

TEST(ServerApplication, DiagnosticsRestartCommunicationsClear)
{
    LONGS_EQUAL(0, hasRestarted);
    uint8_t  data[]      = {0xFF, 0x00};
    uint8_t  request[4];
    uint16_t subFunction = RESTART_COMMUNICATIONS_OPTION;
    UINT16_TO_UINT8_ARRAY(request, 0, subFunction)
    for (uint8_t i = 0; i < 2; i++)
    {
        request[2 + i] = data[i];
    }
    expectResponse(serverAddress, DIAGNOSTICS, request, 4);
    setRead(readPDU, serverAddress, DIAGNOSTICS, request, 4);
    app_update(client);
    check();
    LONGS_EQUAL(1, hasRestarted);
}

TEST(ServerApplication, DiagnosticsReturnDiagnosticRegister)
{
    uint8_t  data[]        = {0x00, 0x00};
    uint16_t registerValue = 0x1234;
    server_dl_set_diag_register(
            server_get_dl(client), registerValue
    );
    uint8_t  response[4];
    uint8_t  request[4];
    uint16_t subFunction   = RETURN_DIAGNOSTIC_REGISTER;
    UINT16_TO_UINT8_ARRAY(request, 0, subFunction)
    UINT16_TO_UINT8_ARRAY(response, 0, subFunction)
    UINT16_TO_UINT8_ARRAY(response, 2, registerValue)
    for (uint8_t i = 0; i < 2; i++)
    {
        request[2 + i] = data[i];
    }
    expectResponse(serverAddress, DIAGNOSTICS, response, 4);
    setRead(readPDU, serverAddress, DIAGNOSTICS, request, 4);
    app_update(client);
    check();
}

TEST(ServerApplication, DiagnosticChangeAsciiInputDelimiter)
{

    uint8_t  data[]      = {0xDD, 0x00};
    uint8_t  request[4];
    uint16_t subFunction = CHANGE_ASCII_INPUT_DELIMITER;
    UINT16_TO_UINT8_ARRAY(request, 0, subFunction)
    for (uint8_t i = 0; i < 2; i++)
    {
        request[2 + i] = data[i];
    }
    expectResponse(serverAddress, DIAGNOSTICS, request, 4);
    setRead(readPDU, serverAddress, DIAGNOSTICS, request, 4);
    app_update(client);
    check();
    LONGS_EQUAL(0xDD, dl_spy_get_delimiter(server_get_dl(client)));
}

TEST(ServerApplication, ForceListenOnlyMode)
{

    uint8_t  data[]      = {0x00, 0x00};
    uint8_t  request[4];
    uint16_t subFunction = FORCE_LISTEN_ONLY_MODE;
    UINT16_TO_UINT8_ARRAY(request, 0, subFunction)
    for (uint8_t i = 0; i < 2; i++)
    {
        request[2 + i] = data[i];
    }
    setRead(readPDU, serverAddress, DIAGNOSTICS, request, 4);
    app_update(client);
    serial_read(serial, readData);
    LONGS_EQUAL(0, readData->size);
}

TEST(ServerApplication, ClearCountersAndDiagnosticRegister)
{
    uint8_t  data[]      = {0x00, 0x00};
    uint8_t  request[4];
    uint16_t subFunction = CLEAR_COUNTERS_AND_DIAGNOSTIC_REGISTER;
    UINT16_TO_UINT8_ARRAY(request, 0, subFunction)
    for (uint8_t i = 0; i < 2; i++)
    {
        request[2 + i] = data[i];
    }
    expectResponse(serverAddress, DIAGNOSTICS, request, 4);
    setRead(readPDU, serverAddress, DIAGNOSTICS, request, 4);
    app_update(client);
    check();
}

TEST(ServerApplication, DiagnosticCounters)
{
    uint16_t     expectedValues[] = {1, 0, 0, 4, 0, 0, 0, 0};
    for (uint8_t i                = BusMessageCount;
         i < BusCharacterOverrunCount; i++)
    {
        testCounter((dl_counter_t) i, expectedValues[i - 11]);
    }
}

TEST(ServerApplication, ClearOverrunCounterAndFlag)
{
    uint8_t  data[]      = {0x00, 0x00};
    uint8_t  request[4];
    uint16_t subFunction = CLEAR_OVERRUN_COUNTER_AND_FLAG;
    UINT16_TO_UINT8_ARRAY(request, 0, subFunction)
    for (uint8_t i = 0; i < 2; i++)
    {
        request[2 + i] = data[i];
    }
    expectResponse(serverAddress, DIAGNOSTICS, request, 4);
    setRead(readPDU, serverAddress, DIAGNOSTICS, request, 4);
    app_update(client);
    check();
}

#if 0
TEST(ServerApplication, GetCommEventCounter)
{

}
TEST(ServerApplication, GetCommEventLog)
{

}

TEST(ServerApplication, ReadDeviceID)
{

}
#endif

TEST(ServerApplication, ReportServerID)
{
    uint8_t expected[] = {serverAddress};
    expectResponse(serverAddress, REPORT_SERVER_ID, expected, 1);

    setRead(readPDU, serverAddress, REPORT_SERVER_ID, {});
    app_update(client);
    check();
}

TEST(ServerApplication, MaskWriteRegister)
{
    testMaskWrite(
            MASK_WRITE_REGISTER,
            0x0004,
            0x00F2,
            0x0025
    );
}

TEST(ServerApplication, ReadWriteMultiple)
{
    testReadWrite(
            HoldingRegisters,
            READ_WRITE_MULTIPLE_REGISTERS,
            0x0003, 0x0006,
            0x000E, 0x0003,
            {0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF},
            {
                    0x00, 0xFE, 0x0A, 0xCD, 0x00,
                    0x01, 0x00, 0x03, 0x00, 0x0D,
                    0x00, 0xFF
            }
    );
}

TEST(ServerApplication, ReadFIFO)
{
    dm_fifo_enqueue(model, 0x04DE, 0x01B8);
    dm_fifo_enqueue(model, 0x04DE, 0x1284);
    setRead(readPDU, serverAddress, READ_FIFO_QUEUE, {0x04, 0xDE});
    uint8_t expected[] = {0x00, 0x06, 0x00, 0x02, 0x01, 0xB8, 0x12, 0x84};
    expectResponse(serverAddress, READ_FIFO_QUEUE, expected, 8);
    app_update(client);
    check();
}
#endif
#endif