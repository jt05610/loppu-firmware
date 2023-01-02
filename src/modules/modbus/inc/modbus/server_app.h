//
// Created by Jonathan Taylor on 5/25/22.
//

#ifndef MICROFLUIDICSYSTEM_SERVER_APP_H
#define MICROFLUIDICSYSTEM_SERVER_APP_H

#include "peripherals.h"
#include "data_model.h"

typedef struct server_app_t * ServerApp;

typedef struct app_init_t
{
    uint8_t address;
    Serial  serial;
    void * ser_inst;
    Timer timer;
    void * tim_inst;
} app_init_t;

ServerApp server_create(app_init_t * params);

void server_update(ServerApp base);

#endif //MICROFLUIDICSYSTEM_SERVER_APP_H