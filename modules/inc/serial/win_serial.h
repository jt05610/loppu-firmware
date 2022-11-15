//
// Created by taylojon on 6/21/2022.
//
#ifdef _WIN32
#ifndef ZETA_WIN_SERIAL_H
#define ZETA_WIN_SERIAL_H

#include "serial/serial.h"

#define DEFAULT_READ_INTERVAL_TO    0
#define DEFAULT_READ_TOT_TO_CONST   100
#define DEFAULT_READ_TOT_TO_MULTI   0
#define DEFAULT_WRITE_TOT_TO_CONST  100
#define DEFAULT_WRITE_TOT_TO_MULTI  0

void win_serial_create(Serial base, SerialInit params);


#endif //ZETA_WIN_SERIAL_H
#endif //_WIN32