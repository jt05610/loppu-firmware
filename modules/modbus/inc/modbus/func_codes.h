/**
  ******************************************************************************
  * @file   func_codes.h
  * @author Jonathan Taylor
  * @date   7/5/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef COMM_FUNC_CODES_H
#define COMM_FUNC_CODES_H


//function codes
#define READ_COILS                              0x01U
#define READ_DISCRETE_INPUTS                    0x02U
#define READ_HOLDING_REGISTERS                  0x03U
#define READ_INPUT_REGISTERS                    0x04U
#define WRITE_SINGLE_COIL                       0x05U
#define WRITE_SINGLE_REGISTER                   0x06U
#define READ_EXCEPTION_STATUS                   0x07U
#define DIAGNOSTICS                             0x08U
#define GET_COMM_EVENT_COUNTER                  0x0BU
#define GET_COMM_EVENT_LOG                      0x0CU
#define WRITE_MULTIPLE_COILS                    0x0FU
#define WRITE_MULTIPLE_REGISTERS                0x10U
#define REPORT_SERVER_ID                        0x11U
#define MASK_WRITE_REGISTER                     0x16U
#define READ_WRITE_MULTIPLE_REGISTERS           0x17U
#define READ_FIFO_QUEUE                         0x18U
#define READ_DEVICE_IDENTIFICATION              0x2BU

// diagnostics subfunctions
#define RETURN_QUERY_DATA                       0x0000U
#define RESTART_COMMUNICATIONS_OPTION           0x0001U
#define RETURN_DIAGNOSTIC_REGISTER              0x0002U
#define CHANGE_ASCII_INPUT_DELIMITER            0x0003U
#define FORCE_LISTEN_ONLY_MODE                  0x0004U
#define CLEAR_COUNTERS_AND_DIAGNOSTIC_REGISTER  0x000AU
#define RETURN_BUS_MESSAGE_COUNT                0x000BU
#define RETURN_BUS_COMMUNICATION_ERROR_COUNT    0x000CU
#define RETURN_BUS_EXCEPTION_ERROR_COUNT        0x000DU
#define RETURN_SERVER_MESSAGE_COUNT             0x000EU
#define RETURN_SERVER_NO_RESPONSE_COUNT         0x000FU
#define RETURN_SERVER_NAK_COUNT                 0x0010U
#define RETURN_SERVER_BUSY_COUNT                0x0011U
#define RETURN_BUS_CHARACTER_OVERRUN_COUNT      0x0012U
#define CLEAR_OVERRUN_COUNTER_AND_FLAG          0x0014U
#endif //COMM_FUNC_CODES_H
