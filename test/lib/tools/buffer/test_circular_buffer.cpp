/**
  ******************************************************************************
  * @file   test_circular_buffer.cpp
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  Tests for circular buffer implementation.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include <gtest/gtest.h>
#include "circular_buffer.h"

#define BUFFER_SIZE 10


class TestCircularBuffer : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void fill_buffer()
    {
        for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
            ASSERT_EQ(0, circ_buf_push(&buffer, i));
            ASSERT_EQ(i, buffer_buffer[i]);
        }
    }

    void clear_buffer()
    {
        uint8_t * ptr = result;
        for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
            ASSERT_EQ(0, circ_buf_pop(&buffer, ptr++));
        }
    }

    CIRC_BUF(buffer, BUFFER_SIZE);
    uint8_t result[BUFFER_SIZE];
};

TEST_F(TestCircularBuffer, push)
{
    fill_buffer();
    ASSERT_EQ(BUFFER_SIZE, buffer.head);
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
        ASSERT_EQ(i, buffer_buffer[i]);
    }
}

TEST_F(TestCircularBuffer, pop)
{
    fill_buffer();
    clear_buffer();
    ASSERT_EQ(buffer.tail, buffer.head);
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
        ASSERT_EQ(i, result[i]);
    }
}

TEST_F(TestCircularBuffer, cant_push_full)
{
    fill_buffer();
    ASSERT_EQ(-1, circ_buf_push(&buffer, 0xFF));

    /* make sure nothing changed */
    ASSERT_EQ(BUFFER_SIZE, buffer.head);
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
        ASSERT_EQ(i, buffer_buffer[i]);
    }
}