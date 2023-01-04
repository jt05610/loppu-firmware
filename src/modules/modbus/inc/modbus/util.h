//
// Created by Jonathan Taylor on 4/21/22.
//

#ifndef VALVECONTROLLER_UTIL_H
#define VALVECONTROLLER_UTIL_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#define  UINT8_TO_UINT16(values, start)                         \
(uint16_t) (256U * (values)[(start)] + (values)[(start) + 1])

#define  UINT8_TO_UINT32(values, start)                         \
(uint32_t) (((values)[(start)] << 24)                           \
            | ((values)[(start) + 1] << 16)                     \
            | ((values)[(start) + 2] << 8)                      \
            | (values)[(start) + 3])

#define UINT16_TO_UINT32(values, start)                         \
(uint32_t) (((values)[(start)] << 16) | (values)[(start) + 1])  \

#define UINT16_TO_UINT8_ARRAY(array, start, value)             \
    (array)[(start)]     = *((uint8_t *) &(value) + 1);       \
    (array)[(start) + 1] = *((uint8_t *) &(value) + 0)


#define UINT32_TO_UINT16_ARRAY(array, start, value)            \
    (array)[(start)]     = *((uint16_t *) &(value) + 1);      \
    (array)[(start) + 1] = *((uint16_t *) &(value) + 0)

#define BYTE_COUNT(quantity)                                    \
    ((quantity) >> 3) + ((quantity) % 8 ? 1 : 0)

static inline uint8_t
build_byte(const uint8_t * bits, uint8_t n)
{
    uint8_t      result = 0;
    for (uint8_t i      = 0; i < n; i++)
        result |= (bits[i] << i);
    return result;

}

uint32_t map(
        uint32_t value, uint32_t inputLow, uint32_t inputHigh,
        uint32_t outputLow, uint32_t outputHigh
);

char * str_combine(const char * start, const char * end);

#endif //VALVECONTROLLER_UTIL_H
