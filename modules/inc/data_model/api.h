/**
  ******************************************************************************
  * @file   api.h
  * @author Jonathan Taylor
  * @date   11/18/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_API_H
#define INJECTOR_API_H

#include <stdbool.h>
#include "modbus.h"
#include "stm32_uart.h"
#include "data_model.h"

#define ADDR 0x01

typedef struct api_t * API;

typedef struct api_t
{
    DataModel     data_model;
    uint16_t      output;
    uint16_t      input;
    mbus_t        mb;
    Modbus_Conf_t modbus_conf;
    uint8_t * rx_buffer;
    uint8_t           receive_buffer[RX_BUFFER_SIZE];
    uint8_t           send_buffer[RX_BUFFER_SIZE];
    volatile uint16_t current_pos;
    volatile uint16_t target_pos;
    volatile bool     new_data;

} api_t;

void api_create(API base, DataModel data_model);

uint16_t api_read(API base, uint32_t address);

uint16_t api_write(API base, uint32_t address, uint16_t value);

uint16_t api_read_handler(uint32_t address);

uint16_t api_write_handler(uint32_t address, uint16_t value);

int api_send_handler(
        const mbus_t context, const uint8_t * data, const uint16_t size);

void api_poll(API base);

#endif //INJECTOR_API_H
