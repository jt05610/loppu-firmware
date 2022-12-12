//
// Created by Jonathan Taylor on 5/25/22.
//

#include "server_dl.h"
#include "modbus/server_app.h"
#include "modbus/util.h"
#include "modbus/data_model.h"
#include "types.h"


#define SERVER_IDLE 0x00
#define SERVER_BUSY 0x01
#define REQ_SUB_FUNC(pdu) UINT8_TO_UINT16((pdu).data.bytes, 0)

static inline void send_response();

static inline void get_device_id();

static struct server_app_t
{
    datalink_t           datalink;
    data_model_t         data_model;
    volatile app_state_t state;
    restart_func_t       restart;
    modbus_pdu_t         pdu;
} self = {0};

ServerApp
server_create(app_init_t * params)
{
    server_dl_create(
            &self.datalink,
            params->address,
            params->rx_buffer,
            &self.pdu,
            params->serial_device,
            params->write_handler
    );
    self.state      = SERVER_IDLE;
    self.restart    = params->restart;
    return &self;
}

void
server_new_data_handler(uint16_t n_bytes)
{
    self.state = SERVER_BUSY;
    self.datalink.target_pos += n_bytes;
}

static inline void
read_exception_status()
{
    self.pdu.data.size++;
    self.pdu.data.bytes[0] = server_dl_get_exception_status();
}

static inline void
handle_diagnostic()
{
    switch (REQ_SUB_FUNC(self.pdu))
    {
        case RETURN_QUERY_DATA:
            break;
        default:
            break;
    }
}

void
server_update(ServerApp base)
{
    if (self.state == SERVER_BUSY)
    {
        if (ReceivedUnicast == dl_update(&base->datalink))
        {
            if (READ_EXCEPTION_STATUS == self.pdu.func_code)
            {
                read_exception_status();
            }
            if (DIAGNOSTICS == self.pdu.func_code)
            {
                handle_diagnostic();
            } else
            {
                datamodel_handle(&self.data_model, &self.pdu, &self.pdu.data);
            }
            send_response();
        }
        self.state = SERVER_IDLE;
    }
}

void
server_attach_device(ServerApp app, void * device, PrimaryTable tables)
{
    app->data_model.device = device;
    datamodel_create(&app->data_model, tables);
}

static inline void
send_response()
{
    server_dl_format_response(&self.pdu.data);
    server_dl_send_response();
}

#if 0
static inline bool
server_update(App base)
{
    bool ret = false;
    if (NewData == dl_update(base->datalink))
    {
        dm_access_result_t result;
        {
            if (request->type == Diagnostic)
                diagnostic_access(self, DIAG_REQ(request), &result);
            else if (request->type == ReadID)
                get_device_id(self, request->request->id, &result);
            else
                dm_access(&self->model, request, &result);

            ret = true;
            destroy_request(request);
        } else
            result.status = IllegalFunction;
        if (ListenOnly == self->state)
            return false;
        if (self->received->address != 0x00)
            send_response(self, &result, self->received->tx_pdu);
    }
    return ret;
}

void
server_destroy(App app)
{
    ServerApp self = (ServerApp) app;
    server_dl_destroy(self->base.datalink);
    free(self->received);
    free(self);
}

Datalink
server_get_dl(App app)
{
    return app->datalink;
}

AccessResult
get_device_id(ServerApp base, IdReq req)
{
    return NULL;
}

AccessResult
diagnostic_access(ServerApp base, DiagnosticReq request)
{
    // todo validate function code
    AccessResult res = calloc(1, sizeof(dm_access_result_t));
    res->result = calloc(1, sizeof(sized_array_t));
    if (request->sub_func == READ_EXCEPTION_STATUS + 0x80)
    {
        res->result->size  = 1;
        res->result->bytes = calloc(res->result->size, sizeof(uint8_t));
        res->result->bytes[0] = server_dl_get_exception_status(
                base->base.datalink
        );
        res->status = AccessOk;
    } else if (request->sub_func == REPORT_SERVER_ID + 0x80)
    {
        res->result->size  = 1;
        res->result->bytes = calloc(res->result->size, sizeof(uint8_t));
        res->result->bytes[0] = server_dl_get_address(base->base.datalink);
        res->status = AccessOk;
    } else if (request->sub_func == RESTART_COMMUNICATIONS_OPTION)
    {
        if (request->data[0])
            server_dl_clear_log(base->base.datalink);
        base->restart(0);
    } else if (request->sub_func == RETURN_DIAGNOSTIC_REGISTER)
    {
        res->result->size  = 2;
        res->result->bytes = calloc(res->result->size, sizeof(uint8_t));
        uint16_t value = server_dl_get_diag_register(
                base->base.datalink
        );
        UINT16_TO_UINT8_ARRAY(res->result->bytes, 0, value)
    } else if (request->sub_func == CHANGE_ASCII_INPUT_DELIMITER)
    {
        dl_set_delimiter(
                base->base.datalink, *((uint8_t *) &(request->data[0]) + 1));
    } else if (request->sub_func == FORCE_LISTEN_ONLY_MODE)
    {
        base->state = ListenOnly;
    } else if (request->sub_func == CLEAR_COUNTERS_AND_DIAGNOSTIC_REGISTER)
    {
        server_dl_clear_counters(base->base.datalink);
        server_dl_set_diag_register(base->base.datalink, 0x0000);
    } else if (0x0B <= request->sub_func && request->sub_func <= 0x12)
    {
        res->result->size  = 2;
        res->result->bytes = calloc(res->result->size, sizeof(uint8_t));
        uint16_t value = server_dl_get_counter(
                base->base.datalink, *((uint8_t *) &(request->sub_func) + 0)
        );
        UINT16_TO_UINT8_ARRAY(res->result->bytes, 0, value)
    } else if (request->sub_func == CLEAR_OVERRUN_COUNTER_AND_FLAG)
    {
        server_dl_set_counter(
                base->base.datalink, BusCharacterOverrunCount, 0x0000
        );
        server_dl_set_exception_status(base->base.datalink, 0, 7);
    } else if (request->sub_func)
    {
        res->status = IllegalFunction;
    }
    return res;
}

ModbusPDU
formatResponse(AccessResult result, ModbusPDU tx_pdu)
{
    if (result->status)
    {
        tx_pdu->func_code += 0x80;
        tx_pdu->data->size  = 1;
        tx_pdu->data->bytes = calloc(tx_pdu->data->size, sizeof(uint8_t));
        tx_pdu->data->bytes[0] = result->status;
        return tx_pdu;
    }
    if (tx_pdu->func_code == READ_EXCEPTION_STATUS
        || tx_pdu->func_code == REPORT_SERVER_ID)
    {
        tx_pdu->data->size  = 1;
        tx_pdu->data->bytes = calloc(tx_pdu->data->size, sizeof(uint8_t));
        tx_pdu->data->bytes[0] = result->result->bytes[0];
        return tx_pdu;
    }
    if (tx_pdu->func_code == DIAGNOSTICS)
    {
        if (result->result->size)
        {
            for (size_t i = 0; i < result->result->size; i++)

                tx_pdu->data->bytes[i + 2] = result->result->bytes[i];
        }
        return tx_pdu;
    }
    if (result->result)
    {
        tx_pdu->data->size =
                tx_pdu->func_code == READ_FIFO_QUEUE ? result->result->size + 2 :
                result->result->size + 1;
        tx_pdu->data->bytes = calloc(tx_pdu->data->size, sizeof(uint8_t));
        if (tx_pdu->func_code == READ_FIFO_QUEUE)
        {
            tx_pdu->data->bytes[0] = 0x00;
            tx_pdu->data->bytes[1] = result->result->size;
            for (size_t i = 0; i < result->result->size; i++)

                tx_pdu->data->bytes[i + 2] = result->result->bytes[i];
        } else
        {
            tx_pdu->data->bytes[0] = result->result->size;
            for (size_t i = 0; i < result->result->size; i++)

                tx_pdu->data->bytes[i + 1] = result->result->bytes[i];
        }
        return tx_pdu;
    }
    if (tx_pdu->func_code == WRITE_MULTIPLE_COILS
        || tx_pdu->func_code == WRITE_MULTIPLE_REGISTERS)
    {
        tx_pdu->data->size = 4;
    }
    return tx_pdu;
}

#endif