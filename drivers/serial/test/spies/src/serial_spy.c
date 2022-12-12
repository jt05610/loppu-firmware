/**
  ******************************************************************************
  * @file   serial_spy.c
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

#include "stdlib.h"
#include "stdio.h"
#include <fcntl.h>
#include "serial_spy.h"
#include <libgen.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include "windows.h"
#endif

char * spy_path()
{
#ifdef _WIN32
    char port_path[500];
    static const char * file_name = "\\fake_serial_port";
    GetCurrentDirectory(500, port_path);
#else
    static const char * file_name = "/fake_serial_port";
    static char       * path      = __FILE__;
    char              * port_path = dirname(dirname(path));
#endif
    uint32_t len = strlen(port_path) + strlen(file_name);
    char * ret;
    ret = calloc(len + 1, sizeof(char));
    strncpy(ret, port_path, len + 1);
    strncat(ret, file_name, len);
    return ret;
}


bool serial_spy_read(uint8_t * data, size_t size)
{
    int fd = open(spy_path(), O_RDONLY);
    read(fd, data, size);
    close(fd);
    return true;
}

bool serial_spy_write(sized_array_t * array)
{
    char * path = spy_path();
    int fd = open(path, O_WRONLY);
    write(fd, array->bytes, array->size);
    close(fd);
    return true;
}

void serial_spy_clear()
{
    FILE * file = fopen(spy_path(), "w");
    fclose(file);
}