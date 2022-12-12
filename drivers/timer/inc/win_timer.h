//
// Created by taylojon on 7/26/2022.
//

#ifndef COMM_WIN_TIMER_H
#define COMM_WIN_TIMER_H
#ifdef WIN32
#include "timer/timer.h"

void win_timer_create(Timer base);

int64_t win_timer_freq();

uint64_t win_time_stamp();
#endif
#endif //COMM_WIN_TIMER_H
