/**
  ******************************************************************************
  * @file   circular_buffer.h
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  Circular buffer header
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_CIRCULAR_BUFFER_H
#define INJECTOR_CIRCULAR_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup Tools
 * @{
 */

/**
 * @defgroup CircularBuffer
 * @brief Volatile circular buffer implementation
 * @{
 */

#include <stdint.h>

/**
 * @brief Circular buffer data structure
 */
typedef struct circ_buf_t
{
    volatile uint8_t * const bytes; /**< @brief Buffer data */
    volatile uint16_t head;         /**< @brief Buffer  */
    volatile uint16_t tail;         /**< @brief Buffer data */
    const uint16_t    size;         /**< @brief Buffer data */
} circ_buf_t;

/**
 * @brief Macro to create circular buffer
 * @param name Name of circular buffer
 * @param size Size of circular buffer
 */
#define CIRC_BUF(name, n)           \
    uint8_t name##_buffer[n+1];     \
    circ_buf_t name = {             \
        .bytes = name##_buffer,     \
        .head = 0,                  \
        .tail = 0,                  \
        .size = n                   \
    }

/**
 * @brief Adds byte to circular buffer
 * @param c Circular buffer instance
 * @param byte Byte to add to buffer
 * @return 0 if successful, -1 on error
 */
static inline char
circ_buf_push(circ_buf_t * c, uint8_t byte)
{
    uint16_t next;

    next = c->head + 1;

    if (next >= c->size + 1) {
        next = 0;
    }
    if (next != c->tail) {
        c->bytes[c->head] = byte;
        c->head = next;
    } else {
        return -1;
    }
    return 0;
}

static inline char
circ_buf_pop(circ_buf_t *c, uint8_t * data)
{
    uint16_t next;
    if (c->head == c->tail)
        return -1;
    next = c->tail + 1;
    if (next >= c->size + 1) {
        next = 0;
    }
    *data = c->bytes[c->tail];
    c->tail = next;
    return 0;
}

/** @) */

/** @) */

#ifdef __cplusplus
};
#endif

#endif //INJECTOR_CIRCULAR_BUFFER_H
