//
// Created by Jonathan Taylor on 5/26/22.
//

#include "event_log.h"

static log_t log = {.count=0, .events = {0}};

void log_create()
{
}

uint16_t
log_get_count()
{
    return log.count;
}

void
log_add(uint8_t event)
{
    if (log.count)
    {
        for (uint8_t i = MAX_LOG_EVENTS-1; i > 0; i--)
        {
            log.events[i] = log.events[i - 1];
        }
        log.events[0] = event;
        log.count++;
    } else
    {
        log.events[0] = event;
        log.count++;
    }
}

uint8_t
log_get_event(uint8_t index)
{
    return log.events[index];
}

void
log_clear()
{
    for (uint8_t i = 0; i < MAX_LOG_EVENTS; i++)
        log.events[i] = 0;
    log.count = 0;
}
