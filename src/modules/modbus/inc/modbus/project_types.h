/**
  ******************************************************************************
  * @file   project_types.h
  * @author Jonathan Taylor
  * @date   6/29/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_PROJECT_TYPES_H
#define DRIVERS_PROJECT_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define RX_BUFFER_SIZE 256

typedef struct sized_array_t {
    uint8_t *bytes;
    uint16_t size;
} sized_array_t;

static inline void
sized_array_create(uint8_t *data, const size_t size, sized_array_t *dest) {
    dest->size = size;
    dest->bytes = data;
}

static inline bool
equal_sized_array(const sized_array_t *first, const sized_array_t *second) {
    bool ret = true;

    if (first->size != second->size) {
        ret = false;
    } else
        for (size_t i = 0; i < first->size; i++) {
            if (first->bytes[i] != second->bytes[i]) {
                ret = false;
                break;
            }
        }
    return ret;
}

#ifdef __cplusplus
};
#endif

#endif //DRIVERS_PROJECT_TYPES_H
