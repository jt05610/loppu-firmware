/**
  ******************************************************************************
  * @file   posix_serial.h
  * @author Jonathan Taylor
  * @date   6/9/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef _WIN32
#ifndef MICROFLUIDICSYSTEM_POSIX_SERIAL_H
#define MICROFLUIDICSYSTEM_POSIX_SERIAL_H

#define POSIX_TURN_ON_DELAY_ms 1650
#define POSIX_READ_DELAY_ms 12

#include "termios.h"
#include "fcntl.h"
#include "serial.h"
#include "../../timer/inc/timer.h"

typedef enum parity_t
{
    NO_PARITY,
    EVEN_PARITY,
    ODD_PARITY
} parity_t;

typedef enum input_t
{
    CANONICAL_INPUT,
    RAW_INPUT
} input_t;

typedef enum enable_t
{
    DISABLE = false,
    ENABLE  = true
} enable_t;

typedef enum char_size_t
{
    FIVE_BITS  = CS5,
    SIX_BITS   = CS6,
    SEVEN_BITS = CS7,
    EIGHT_BITS = CS8
} char_size_t;

typedef enum blocking_t
{
    BLOCKING = 0,
    NON_BLOCKING = FNDELAY
} blocking_t;

typedef enum output_t
{
    PROCESSED_OUTPUT,
    RAW_OUTPUT
} output_t;

typedef struct termios termios_t;

typedef termios_t * termios_p;

#define DEFAULT_OPTIONS (O_RDWR | O_NOCTTY | O_NDELAY)
#define DEFAULT_PARITY NO_PARITY
#define DEFAULT_INPUT RAW_INPUT
#define DEFAULT_CHAR_SIZE EIGHT_BITS
#define DEFAULT_FLOW_CONTROL DISABLE
#define DEFAULT_ECHO DISABLE
#define DEFAULT_BLOCKING BLOCKING
#define DEFAULT_OUTPUT RAW_OUTPUT
#define DEFAULT_TIMEOUT 0
#define DEFAULT_MIN_CHAR_READ 0

void posix_serial_set_timer(Timer time);

void posix_serial_create(Serial base, SerialInit params);

void posix_serial_set_parity(Serial base, parity_t parity);

void posix_serial_set_input_type(Serial base, input_t parity);

void posix_serial_set_flow_control(Serial base, enable_t enable);

void posix_serial_set_echo(Serial base, enable_t enable);

void posix_serial_set_char_size(Serial base, char_size_t size);

void posix_serial_set_blocking(Serial base, blocking_t blocking);

void posix_serial_set_output(Serial base, output_t output);

void posix_serial_set_timeout(Serial base, uint8_t timeout);

void posix_serial_set_min_char_read(Serial base, uint8_t value);

termios_p posix_serial_get_termios(Serial base);

int posix_serial_get_file_descriptor(Serial base);

int posix_serial_get_options();

#endif //MICROFLUIDICSYSTEM_POSIX_SERIAL_H
#endif //_WIN32
