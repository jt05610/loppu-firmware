//
// Created by Jonathan Taylor on 5/19/22.
//

#ifndef MICROFLUIDICSYSTEM_DATALINK_PRIVATE_H
#define MICROFLUIDICSYSTEM_DATALINK_PRIVATE_H

#ifndef MICROFLUIDICSYSTEM_DATALINK_H
#include "datalink.h"
#endif

#include "types.h"


#define N_ERROR_COUNTERS 8
typedef struct datalink_interface_t
{
    dl_update_t (* update)(void);

    void (* handle_error)(void);

    void (* reset_comm_log)(void);

    uint16_t (* get_counter)(dl_counter_t counter);

    void (* clear_counters)(void);

    void (* clear_counter)(dl_counter_t counter);

    void (* write_handler)(void * serial_obj, uint8_t * bytes, uint16_t n);

} datalink_interface_t;

typedef struct datalink_t
{
    DatalinkInterface vtable;
    void * serial_device;
    volatile uint8_t * buffer;
    uint16_t current_pos;
    uint16_t target_pos;
    const char * type;
} datalink_t;

#endif //MICROFLUIDICSYSTEM_DATALINK_PRIVATE_H
