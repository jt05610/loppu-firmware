/**
  ******************************************************************************
  * @file   posix_timer.h
  * @author Jonathan Taylor
  * @date   7/29/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef DRIVERS_POSIX_TIMER_H
#define DRIVERS_POSIX_TIMER_H
#ifndef WIN32

#include "timer/timer.h"

void posix_timer_create(Timer time);

struct timeval * posix_time_stamp();

#endif
#endif //DRIVERS_POSIX_TIMER_H
