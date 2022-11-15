//
// Created by taylojon on 7/26/2022.
//

#ifdef WIN32
#include <windows.h>
#include "timer/win_timer.h"

static struct win_timer
{
    Timer   base;
    int64_t us_freq;
    int64_t ms_freq;
    LARGE_INTEGER counter;
    FILETIME file_time;
    ULARGE_INTEGER time_large;
} self = {0};

#define UPDATE  QueryPerformanceCounter(&self.counter)


static inline time_amount_t
micros()
{
    UPDATE;
    return self.counter.QuadPart / self.us_freq;
}

static inline time_amount_t
millis()
{
    UPDATE;
    return self.counter.QuadPart / self.ms_freq;
}

static void
delay(time_amount_t ms)
{
    time_amount_t start = millis();
    while (millis() - start < ms);
}

static void
delay_micros(time_amount_t us)
{

    time_amount_t start = micros();
    while (micros() - start < us);
}

static timer_interface_t win_t_interface = {
        .delay=delay,
        .delay_micros=delay_micros,
        .micros=micros,
        .millis=millis
};

void
win_timer_create(Timer base)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    self.us_freq = freq.QuadPart / 1000000;
    self.ms_freq = self.us_freq * 1000;
    base->vtable = &win_t_interface;
}

int64_t
win_timer_freq()
{
    return self.us_freq;
}

uint64_t win_time_stamp()
{
    GetSystemTimePreciseAsFileTime(&self.file_time);
    self.time_large.LowPart = self.file_time.dwLowDateTime;
    self.time_large.HighPart = self.file_time.dwHighDateTime;
    return self.time_large.QuadPart;
}

#endif