/**
  ******************************************************************************
  * @file   stm32_device_id.c
  * @author Jonathan Taylor
  * @date   1/19/24
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * This file is part of a project licensed under the MIT License.
  * For more information, see the LICENSE.md file in the project root.
  *
  ******************************************************************************
  */

#include "stm32g0xx_ll_utils.h"
#include "stm32_device_id.h"

void uint32_to_hex_str(const uint32_t value, char *buffer) {
    for (int i = 0; i < 8; i++) {
        const uint8_t byte = (value >> ((7 - i) * 4)) & 0xF;
        buffer[i] = byte < 10 ? '0' + byte : 'A' + byte - 10;
    }
    buffer[8] = '\0'; // null-terminate the string
}

const char *stm32_get_device_id() {
    uint32_t words[3];
    words[0] = LL_GetUID_Word0();
    words[1] = LL_GetUID_Word1();
    words[2] = LL_GetUID_Word2();
    static char id[25];
    uint32_to_hex_str(words[0], id);
    uint32_to_hex_str(words[1], id + 8);
    uint32_to_hex_str(words[2], id + 16);
    return id;
}
