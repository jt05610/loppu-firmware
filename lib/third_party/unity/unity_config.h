/**
  ******************************************************************************
  * @file   unity_config.h
  * @author Jonathan Taylor
  * @date   12/14/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "serial.h"

#ifndef INJECTOR_UNITY_CONFIG_H
#define INJECTOR_UNITY_CONFIG_H
#define UNITY_INT_WIDTH 16
#define UNITY_POINTER_WIDTH 16
#define CMOCK_MEM_INDEX_TYPE uint16_t
#define CMOCK_MEM_PTR_AS_INT uint16_t
#define CMOCK_MEM_ALIGN 1
#define CMOCK_MEM_SIZE 4096

void unity_output_attach_serial(Serial serial);

void unity_output_start();

uint8_t unity_output_char(char a);

void unity_output_flush();

void unity_output_complete();

#define UNITY_OUTPUT_START unity_output_start
#define UNITY_OUTPUT_CHAR unity_output_char
#define UNITY_OUTPUT_FLUSH unity_output_flush
#define UNITY_OUTPUT_COMPLETE unity_output_complete

#endif