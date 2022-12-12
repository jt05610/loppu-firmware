//
// Created by taylojon on 6/21/2022.
//

#ifdef _WIN32
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

#include "serial/win_serial.h"

#define RX_BUFF_SIZE 256

static struct win_serial_t
{
    Serial     base;
    const char * port;
    HANDLE       handle;
    COMMTIMEOUTS timeouts;
    DCB state;
    uint8_t * rx_buffer;
} self = {0};

static CommPortList
win_serial_list_ports()
{
    CommPortList list = calloc(1, sizeof(comm_port_list_t));
    list->n_ports = 0;
    char device[5000];
    for (int i = 0; i < 255; i ++)
    {
        char comm[7];
        sprintf(comm, "COM%d", i);
        DWORD test = QueryDosDevice(comm, device, sizeof(device));

        if (test != 0)
        {
            list->ports[list->n_ports] = calloc(1, sizeof(comm_port_t));
            list->ports[list->n_ports]->device = device;
            list->ports[list->n_ports]->name = comm;
            list->n_ports++;
        }
    }
    return list;
}

#define EXIT_ON_ERROR(func, ...) {  \
    BOOL success;                   \
    success = (func)(__VA_ARGS__);  \
    if (!success)                   \
    {                               \
        CloseHandle(self.handle);  \
        return false;               \
    }                               \
}

static bool
win_serial_open()
{
    self.handle = CreateFileA(
            self.port,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
            );
    if (self.handle == INVALID_HANDLE_VALUE)
        return false;
    EXIT_ON_ERROR(FlushFileBuffers, self.handle)
    EXIT_ON_ERROR(SetCommTimeouts, self.handle, &self.timeouts)
    EXIT_ON_ERROR(SetCommState, self.handle, &self.state)
    return true;
}

static bool
win_serial_write(const sized_array_t * data)
{
    DWORD written;
    BOOL success = WriteFile(
            self.handle,
            data->bytes,
            data->size,
            &written,
            NULL);
    if (!success)
        return false;
    if (written != data->size)
        return false;
    return true;
}

static bool
win_serial_read(sized_array_t * dest)
{
    bool ret = false;
    DWORD received;
    BOOL success = ReadFile(
            self.handle,
            self.rx_buffer, RX_BUFF_SIZE, &received, NULL);
    if (success)
    {
        dest->bytes = self.rx_buffer;
        dest->size = received;
        ret = true;
    }
    return ret;
}

static bool
win_serial_close()
{
    if (self.handle != INVALID_HANDLE_VALUE)
    {
        FlushFileBuffers(self.handle);
        CloseHandle(self.handle);
    }
    return true;
}

serial_interface_t win_serial_interface = {
        .open=win_serial_open,
        .close=win_serial_close,
        .read=win_serial_read,
        .write=win_serial_write,
        .list_ports=win_serial_list_ports
};

void
win_serial_create(Serial base, SerialInit params)
{
    self.port = params->port;
    self.base = base;
    base->vtable = &win_serial_interface;
    base->baud = params->baud;
    self.rx_buffer = params->rx_buffer;

    self.handle                       = INVALID_HANDLE_VALUE;
    self.timeouts.ReadIntervalTimeout = DEFAULT_READ_INTERVAL_TO;
    self.timeouts.ReadTotalTimeoutConstant = DEFAULT_READ_TOT_TO_CONST;
    self.timeouts.ReadTotalTimeoutMultiplier = DEFAULT_READ_TOT_TO_MULTI;
    self.timeouts.WriteTotalTimeoutConstant = DEFAULT_WRITE_TOT_TO_CONST;
    self.timeouts.WriteTotalTimeoutMultiplier = DEFAULT_WRITE_TOT_TO_MULTI;

    self.state.DCBlength = sizeof(DCB);
    self.state.BaudRate = params->baud;
    self.state.ByteSize = 8;
    self.state.Parity = NOPARITY;
    self.state.StopBits = ONESTOPBIT;
}

#endif //_WIN32

