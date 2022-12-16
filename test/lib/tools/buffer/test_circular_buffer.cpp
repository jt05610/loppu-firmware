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
#include "buffer/circular_buffer.h"

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
            circ_buf_push(&buffer, i);
            ASSERT_EQ(i, buffer_buffer[i + buffer.tail]);
        }
    }

    void clear_buffer()
    {
        for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
            ASSERT_EQ(i, circ_buf_pop(&buffer));
        }
    }

    CIRC_BUF(buffer, BUFFER_SIZE);
    uint8_t result[BUFFER_SIZE];
};

TEST_F(TestCircularBuffer, push)
{
    fill_buffer();
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
        ASSERT_EQ(i, buffer_buffer[i]);
    }
}

TEST_F(TestCircularBuffer, pop)
{
    fill_buffer();
    clear_buffer();
}

TEST_F(TestCircularBuffer, waiting)
{
    fill_buffer();
    ASSERT_EQ(BUFFER_SIZE, circ_buf_waiting(&buffer));
    for (uint8_t i = 0; i < BUFFER_SIZE; i++) {
        circ_buf_pop(&buffer);
        ASSERT_EQ(BUFFER_SIZE - 1, circ_buf_waiting(&buffer));
        circ_buf_push(&buffer, 0xFF);
        ASSERT_EQ(BUFFER_SIZE, circ_buf_waiting(&buffer));
    }
}

TEST_F(TestCircularBuffer, transfer)
{
    CIRC_BUF(dest, 256);
    for (uint8_t i = 1; i < 26; i++) {
        fill_buffer();
        circ_buf_transfer(&dest, &buffer);
        ASSERT_EQ((i * BUFFER_SIZE), circ_buf_waiting(&dest));
    }
}