//
// Created by Jonathan Taylor on 5/19/22.
//
#include "modbus/datalink.h"
#include "modbus/pdu_types.h"
#include "buffer/circular_buffer.h"

static uint8_t      buffer[RX_BUFFER_SIZE - 4];
static modbus_pdu_t mod_pdu = {0};
static serial_pdu_t rx_pdu  = {0};

typedef struct datalink_t
{
    volatile uint8_t state;
    volatile bool    new_data;
    Serial           serial;
    SerialPDU        rx_pdu;
    SerialPDU        tx_pdu;
    Timer            timer;
    uint8_t          addr;
    void * serial_instance;
} datalink_t;

static datalink_t self = {0};

static uint8_t init(Datalink dl);

static uint8_t idle_handler(Datalink dl);

static uint8_t rx_handler(Datalink dl);

static uint8_t control_handler(Datalink dl);

Datalink
dl_create(Serial serial, Timer timer, void * serial_inst, uint8_t addr)
{
    self.new_data        = false;
    self.serial          = serial;
    self.timer           = timer;
    self.serial_instance = serial_inst;
    mod_pdu.data.bytes   = buffer;
    mod_pdu.data.size    = 0;
    self.rx_pdu          = &rx_pdu;
    self.rx_pdu->pdu     = &mod_pdu;
    self.state           = init(&self);
    self.addr            = addr;
    return &self;
}

static uint8_t (* handlers[])(Datalink) = {
        idle_handler,
        rx_handler,
        control_handler,
};

uint8_t
dl_update(Datalink base)
{
    base->state = handlers[base->state](base);
    return base->state;
}

static void
serial_rx_cb()
{
    self.state = DL_CONTROL_STATE;
}

bool
dl_new_data(Datalink base)
{
    return base->new_data;
}

void
dl_reset(Datalink base)
{
    base->new_data = false;
    base->state    = DL_IDLE_STATE;
}

ModbusPDU dl_rx_pdu(Datalink base)
{
    return base->rx_pdu->pdu;
}

void dl_send(Datalink base, ModbusPDU pdu)
{
    if (base->rx_pdu->address != 0x00) {
        sized_array_t to_send;
        pdu_format(base->rx_pdu->address, pdu, base->rx_pdu);
        serialize_serial_pdu(base->rx_pdu, &to_send);
        serial_write(
                base->serial, base->serial_instance, to_send.bytes,
                to_send.size);
    } else {

    }
    serial_clear(base->serial, base->serial_instance);
}

uint8_t
init(Datalink dl)
{
    serial_register_rx_callback(dl->serial, dl->serial_instance, serial_rx_cb);
    serial_open(dl->serial, dl->serial_instance);
    //timer_register_update_callback( dl->timer, dl->half_char_timer, tim_update_cb);
    //timer_set_timeout(dl->timer, dl->half_char_timer, 50);
    //timer_start(self.timer, self.half_char_timer, (115200 / 11));
    //timer_stop(self.timer, self.half_char_timer);
    return DL_IDLE_STATE;
}

uint8_t
idle_handler(Datalink dl)
{
    if (serial_available(dl->serial, dl->serial_instance)) {
        dl->state = DL_CONTROL_STATE;
    }
    return dl->state;
}

uint8_t
rx_handler(Datalink dl)
{
    if (serial_available(dl->serial, dl->serial_instance) > 4) {
        dl->state = DL_CONTROL_STATE;
    }
    return dl->state;
}

uint8_t
control_handler(Datalink dl)
{
    uint16_t size = serial_available(dl->serial, dl->serial_instance);
    if (size) {
        dl->rx_pdu->pdu->data.size = size - 4;
        while (size--) {
            process_byte(dl->rx_pdu, circ_buf_pop(dl->serial->serial_buffer));
        }
        self.new_data = (pdu_is_valid(dl->rx_pdu) &&
                         (dl->rx_pdu->address == 0 ||
                          dl->rx_pdu->address == self.addr));

        serial_clear(dl->serial, dl->serial_instance);
    } else {
        serial_clear(dl->serial, dl->serial_instance);
    }
    return DL_IDLE_STATE;
}
