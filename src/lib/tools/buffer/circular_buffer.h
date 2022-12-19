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

#include "buffer/copy.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup Tools
 * @{
 */

/**
 * @defgroup CircularBuffer Circular buffer
 * @brief Volatile circular buffer implementation
 * @{
 */

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Circular buffer data structure
 */
typedef struct circ_buf_t
{
    volatile uint8_t * const bytes; /**< @brief Buffer data */
    volatile uint16_t head;         /**< @brief Buffer  */
    volatile uint16_t tail;         /**< @brief Buffer data */
    const uint16_t    size;         /**< @brief Buffer data */
    bool empty;        /**< @brief Whether buffer is empty */
} circ_buf_t;

/**
 * @brief Macro to create circular buffer
 * @param name Name of circular buffer
 * @param size Size of circular buffer
 */
#define CIRC_BUF(name, n)           \
    uint8_t name##_buffer[n];       \
    circ_buf_t name = {             \
        .bytes = name##_buffer,     \
        .head = 0,                  \
        .tail = 0,                  \
        .size = n                   \
    }

/**
 * @brief Macro to create static circular buffer
 * @param name Name of circular buffer
 * @param size Size of circular buffer
 */
#define STATIC_CIRC_BUF(name, n)        \
    static uint8_t name##_buffer[n];    \
    static circ_buf_t name = {          \
        .bytes = name##_buffer,         \
        .head = 0,                      \
        .tail = 0,                      \
        .size = n,                      \
        .empty = true, \
    }

/**
 * @brief Adds byte to circular buffer
 * @param c Circular buffer instance
 * @param byte Byte to add to buffer
 */
static inline void
circ_buf_push(circ_buf_t * c, uint8_t byte)
{
    c->bytes[c->head++] = byte;
    c->head %= c->size;
    c->empty            = false;
}

/**
 * @brief Copies next byte in buffer to given buffer
 * @param c Circular buffer instance
 */
static inline uint8_t
circ_buf_pop(circ_buf_t * c)
{
    uint8_t result = c->bytes[c->tail++];
    c->tail %= c->size;
    c->empty       = c->tail == c->head;
    return result;
}

/**
 * @brief Gives how many bytes are waiting to be transferred from buffer.
 * @param c Circular buffer instance
 * @return number of bytes in buffer
 */
static inline uint16_t
circ_buf_waiting(circ_buf_t * c)
{
    if (c->head > c->tail) {
        return c->head - c->tail;
    } else if (c->head == c->tail) {
        if (!c->empty) {
            return c->size;
        } else {
            return 0;
        }
    } else {
        return c->size - (c->tail - c->head);
    }

}

/**
 * @brief Copies from one circular buffer to another
 * @param dest Buffer to copy to
 * @param src Buffer to copy from
 * @return true if okay, otherwise false
 */
static inline bool
circ_buf_transfer(circ_buf_t * dest, circ_buf_t * src)
{
    uint16_t n = circ_buf_waiting(src);
    if (n > dest->size) {
        return false;
    }
    for (uint16_t i = 0; i < n; i++) {
        circ_buf_push(dest, circ_buf_pop(src));
    }
    return true;
}

/** @) */

/** @) */

#ifdef __cplusplus
}
#endif

#endif //INJECTOR_CIRCULAR_BUFFER_H
