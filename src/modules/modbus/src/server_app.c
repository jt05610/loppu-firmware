//
// Created by Jonathan Taylor on 5/25/22.
//

#include "modbus/server_app.h"
#include "modbus/util.h"
#include "modbus/data_model.h"
#include "modbus/datalink.h"

#define SERVER_IDLE 0x00
#define SERVER_BUSY 0x01

static struct server_app_t
{
    Datalink         datalink;
    DataModel        data_model;
    volatile uint8_t state;
} self = {0};

ServerApp
server_create(app_init_t * params)
{
    self.datalink = dl_create(
            params->serial, params->timer, params->ser_inst, params->address);

    self.state    = SERVER_IDLE;
    self.data_model = params->data_model;
    return &self;
}

void
server_update(ServerApp base)
{
    dl_update(base->datalink);
    if (dl_new_data(base->datalink)) {
        datamodel_handle(base->data_model, dl_rx_pdu(base->datalink));
        dl_send(base->datalink, dl_rx_pdu(base->datalink));
        dl_reset(base->datalink);
    }
}