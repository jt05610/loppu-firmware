/**
  ******************************************************************************
  * @file   FakeSerial.c
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

#include <stdio.h>
#include <string.h>

#include "../../../../modbus/inc/public/modbus/project_types.h"
#include "serial_spy.h"

#include "fake_serial.h"

static struct fake_serial_t
{
    FILE       * file_p;
    const char * port;
    uint8_t    * rx_buffer;
    char    options[3];
    size_t  written;
    uint8_t ptr[300];
} self = {0};

static bool fake_serial_open();

static bool fake_serial_close();

static bool fake_serial_read(sized_array_t * data);

static bool fake_serial_write(const sized_array_t * data);

static void fake_serial_set_options(serial_opt_t options);

serial_interface_t fake_interface = {
        .open = fake_serial_open,
        .close = fake_serial_close,
        .read = fake_serial_read,
        .write = fake_serial_write,
        .set_options=fake_serial_set_options
};

void
fake_serial_create(Serial base, SerialInit params)
{
    self.port      = params->port;
    base->baud     = params->baud;
    base->vtable   = &fake_interface;
    self.rx_buffer = params->rx_buffer;
}

static bool
fake_serial_open()
{
    bool ret = false;
    self.file_p = fopen(self.port, self.options);
    if (self.file_p)
        ret = true;
    return ret;
}

static bool
fake_serial_close()
{
    bool ret = true;
    if (self.file_p)
        fclose(self.file_p);
    self.file_p = NULL;
    return ret;
}

static bool
fake_serial_read(sized_array_t * data)
{
    bool ret = false;
    data->size = 0;
    fake_serial_set_options(SerialReadOnly);
    fake_serial_open();

    while (true)
    {
        uint8_t c = fgetc(self.file_p);
        if (feof(self.file_p))
        {
            break;
        }
        self.rx_buffer[data->size++] = c;
    }

    if (data->size)
        ret = true;
    data->bytes = self.rx_buffer;
    fake_serial_close();
    serial_spy_clear();
    return ret;
}

static bool
fake_serial_write(const sized_array_t * data)
{
    bool         ret = true;
    for (uint8_t i   = 0; i < data->size; i++)
        self.ptr[i] = data->bytes[i];

    fake_serial_set_options(SerialWriteOnly);
    fake_serial_open();
    self.ptr[data->size] = '\0';
    self.written = fwrite(
            self.ptr,
            sizeof(uint8_t),
            data->size, self.file_p
    );

    if (self.written != data->size)
        ret = false;
    fake_serial_close();
    return ret;
}

static void
fake_serial_set_options(serial_opt_t options)
{
    switch (options)
    {
        case SerialReadOnly:
            strcpy(self.options, "r");
            break;
        case SerialReadWrite:
            strcpy(self.options, "r+");
            break;
        case SerialWriteOnly:
            strcpy(self.options, "w");
            break;
        default:
            break;
    }
}