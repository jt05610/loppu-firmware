//
// Created by Jonathan Taylor on 5/26/22.
//

#ifndef MICROFLUIDICSYSTEM_EVENT_LOG_H
#define MICROFLUIDICSYSTEM_EVENT_LOG_H

#include <stdint.h>

#define MAX_LOG_EVENTS 32

typedef struct log_t
{
    uint8_t events[MAX_LOG_EVENTS];
    uint8_t count;
} log_t;

void log_create();

uint16_t log_get_count();

void log_add(uint8_t event);

uint8_t log_get_event(uint8_t index);

void log_clear();

#endif //MICROFLUIDICSYSTEM_EVENT_LOG_H
