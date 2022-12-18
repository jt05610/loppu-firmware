/**
  ******************************************************************************
  * @file   copy.h
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_COPY_H
#define INJECTOR_COPY_H

#include "stddef.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef EMBEDDED
#define BYTE_BUFFER_TYPE volatile uint8_t * restrict
#else
#define BYTE_BUFFER_TYPE volatile uint8_t *
#endif

/**
 * Copy volatile buffer from one to another
 * @param dest destination buffer
 * @param src source buffer
 * @param n number of bytes to transfer
 */
static inline volatile void *
copy(
        BYTE_BUFFER_TYPE dest,
        const BYTE_BUFFER_TYPE src,
        size_t n)
{
    const volatile uint8_t * src_c  = src;
    volatile uint8_t       * dest_c = dest;

    while (n > 0) {
        n--;
        dest_c[n] = src_c[n];
    }
    return dest;
}

#ifdef __cplusplus
};
#endif
#endif //INJECTOR_COPY_H
