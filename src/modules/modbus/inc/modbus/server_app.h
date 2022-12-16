//
// Created by Jonathan Taylor on 5/25/22.
//

#ifndef MICROFLUIDICSYSTEM_SERVER_APP_H
#define MICROFLUIDICSYSTEM_SERVER_APP_H

#include "data_model.h"

typedef struct server_app_t * ServerApp;

typedef struct app_init_t
{
    uint8_t address;
    volatile uint8_t * rx_buffer;
    void * serial_device;
    void (*write_handler) (void * serial_obj, uint8_t * bytes, uint16_t n);
    void (*restart)(void *);
} app_init_t;

typedef uint8_t app_state_t;

ServerApp server_create(app_init_t * params);

void server_new_data_handler(uint16_t n_bytes);

void server_attach_device(ServerApp app, void * device, PrimaryTable tables);

void server_update(ServerApp base);

#endif //MICROFLUIDICSYSTEM_SERVER_APP_H