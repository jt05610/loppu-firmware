//
// Created by Jonathan Taylor on 5/26/22.
//

#include "CppUTest/TestHarness.h"

extern "C"
{
#include ".private/event_log.h"
}

TEST_GROUP(EventLog)
{

    void setup() override
    {
        log_create();
    }

    void teardown() override
    {
        log_clear();
    }
};

TEST(EventLog, Create)
{
    LONGS_EQUAL(0, log_get_count());
}

TEST(EventLog, AddEventToEmptyLog)
{
    log_add(0x05);
    LONGS_EQUAL(0x05, log_get_event(0));
    LONGS_EQUAL(1, log_get_count());
}

TEST(EventLog, AddEventToLogWithEntry)
{
    log_add(0x05);
    LONGS_EQUAL(0x05, log_get_event(0));
    log_add(0x06);
    LONGS_EQUAL(0x05, log_get_event(1));
    LONGS_EQUAL(0x06, log_get_event(0));
    LONGS_EQUAL(2, log_get_count());
}

TEST(EventLog, AddEventToFullLog)
{
    for (int i = 0; i < MAX_LOG_EVENTS; i++)
    {
        log_add(i);
        LONGS_EQUAL(i, log_get_event(0));
    }
    log_add(0xFF);
    LONGS_EQUAL(1, log_get_event(MAX_LOG_EVENTS-1));
    LONGS_EQUAL(2, log_get_event(MAX_LOG_EVENTS-2));
    LONGS_EQUAL(MAX_LOG_EVENTS+1, log_get_count());
    log_add(0xFF);
    LONGS_EQUAL(2, log_get_event(MAX_LOG_EVENTS-1));
    LONGS_EQUAL(MAX_LOG_EVENTS+2, log_get_count());
}