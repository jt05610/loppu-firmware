//
// Created by Jonathan Taylor on 5/8/22.
//
#include "event_log.h"
#include "server_dl.h"

#define ERROR_DECIMAL(error) ((error)-11)
#define INCREMENT_COUNTER(self, error) \
((self).errorCounters[ERROR_DECIMAL((error))]++)

#define PDU_BUFFER_SIZE 252

static struct server_dl_t
{
    Datalink     base;
    uint8_t      address;
    uint8_t      exceptionStatus;
    uint16_t     diagnosticRegister;
    uint16_t     errorCounters[ERROR_COUNTERS];
    serial_pdu_t received;
    uint8_t      pdu_buffer[PDU_BUFFER_SIZE];
} self = {0};

uint16_t
server_dl_get_counter(dl_counter_t error)
{
    return self.errorCounters[ERROR_DECIMAL(error)];
}

static inline void
clear_errors(void)
{
    for (uint8_t i = 0; i < ERROR_COUNTERS; i++)
    {
        self.errorCounters[i] = 0;
    }
}

static inline dl_update_t
server_dl_update()
{
    dl_update_t ret = dl_receive(self.base, &self.received);
    if (ReceivedBroadcast == ret || ReceivedUnicast == ret)
    {
        if (!dl_crc_check(&self.received))
        {
            INCREMENT_COUNTER(self, BusCommunicationErrorCount);
            ret = FrameError;
        } else
        {
            INCREMENT_COUNTER(self, BusMessageCount);
            if (self.received.address == self.address)
            {
                INCREMENT_COUNTER(self, ServerMessageCount);
            } else if (0x00 == self.received.address)
                INCREMENT_COUNTER(self, ServerNoResponseCount);
        }
    }
    return ret;
}

static datalink_interface_t server_interface = {
        .handle_error=0,
        .update=server_dl_update
};

void
server_dl_create(
        Datalink base,
        uint8_t address,
        uint8_t * rx_buffer,
        ModbusPDU pdu,
        void * serial_device,
        write_handler_t write_handler
)
{
    server_interface.write_handler = write_handler;
    base->serial_device = serial_device;
    self.address                  = address;
    base->vtable                  = &server_interface;
    base->type                    = "ServerDataLink";
    base->buffer                  = rx_buffer;
    self.base                     = base;
    base->current_pos             = 0;
    base->target_pos              = 0;
    self.diagnosticRegister       = 0x0000;
    self.received.pdu             = pdu;
    self.received.pdu->data.bytes = self.pdu_buffer;
    log_create();
    clear_errors();
}

uint8_t server_dl_get_exception_status()
{
    return self.exceptionStatus;
}

void server_dl_set_exception_status(uint8_t status, uint8_t output)
{
    if (status)
    {
        self.exceptionStatus |= (0x01 << output);
    } else
    {
        self.exceptionStatus &= ~(0x01 << output);
    }
}

uint8_t
server_dl_get_address()
{
    return self.address;
}

void
server_dl_set_diag_register(uint16_t value)
{
    self.diagnosticRegister = value;
}

uint16_t server_dl_get_diag_register()
{
    return self.diagnosticRegister;
}

void
server_dl_clear_counters()
{
    for (uint8_t i = 0; i < ERROR_COUNTERS; i++)
    {
        self.errorCounters[i] = 0;
    }
}

void
server_dl_set_counter(dl_counter_t counter, uint16_t value)
{
    self.errorCounters[ERROR_DECIMAL(counter)] = value;
}

void
server_dl_format_response(sized_array_t * result)
{
    if (result->size)
    {
        for (uint8_t i = result->size; i > 0; i--)
        {
            self.received.pdu->data.bytes[i] =
                    self.received.pdu->data.bytes[i - 1];
        }

        self.received.pdu->data.bytes[0] = result->size;
        self.received.pdu->data.size = result->size + 1;
        self.received.crc = dl_crc16(
                self.received.address, self.received.pdu
        );
    } else {
        result->size = 4;
    }
}

void
server_dl_send_response()
{
    dl_transmit(self.base, &self.received);
}