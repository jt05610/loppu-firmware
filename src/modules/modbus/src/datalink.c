//
// Created by Jonathan Taylor on 5/19/22.
//
#include "modbus/datalink.h"
#include "modbus/pdu_types.h"

#define HALF_CHAR_TIME(baud) ((baud) / 39)

typedef struct datalink_t
{
    volatile uint8_t state;
    volatile bool    new_data;
    Serial           serial;
    SerialPDU        rx_pdu;
    SerialPDU        tx_pdu;
    Timer            timer;
    void * serial_instance;
    void * half_char_timer;
} datalink_t;

static datalink_t self = {0};

static inline uint8_t init(Datalink dl);

static inline void tim_update_cb(void);

static inline void serial_rx_cb(void);

static inline uint8_t idle_handler(Datalink dl);

static inline uint8_t rx_handler(Datalink dl);

static inline uint8_t control_handler(Datalink dl);

static inline uint8_t tx_handler(Datalink dl);

Datalink
dl_create(Serial serial, Timer timer, void * serial_inst, void * tim_inst)
{
    self.new_data = false;
    self.serial = serial;
    self.timer = timer;
    self.serial_instance = serial_inst;
    self.half_char_timer = tim_inst;

    self.state = init(&self);

    return &self;
}

uint8_t
dl_update(Datalink base)
{
    static uint8_t (* handlers[])(Datalink) = {
            idle_handler,
            rx_handler,
            control_handler,
            tx_handler,
    };

    return handlers[base->state](base);
}

static inline void
tim_update_cb(void)
{
    if (self.state == DL_RX_STATE) {
        self.state = DL_CONTROL_STATE;
    } else {
        self.state = DL_IDLE_STATE;
    }
}

static inline void
serial_rx_cb()
{
    timer_reset(self.timer, self.half_char_timer);
    self.state = DL_RX_STATE;
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
}

ModbusPDU dl_rx_pdu(Datalink base)
{
    return base->rx_pdu->pdu;
}

void dl_send(Datalink base, ModbusPDU pdu)
{
    if (base->rx_pdu->address != 0x00) {

    } else {

    }
}

uint8_t
init(Datalink dl)
{
    timer_start(dl->timer, dl->half_char_timer, HALF_CHAR_TIME(115200));
    serial_open(dl->serial, dl->serial_instance);
    timer_register_update_callback(
            dl->timer, dl->half_char_timer, tim_update_cb);
    serial_register_rx_callback(dl->serial, dl->serial_instance, serial_rx_cb);
    return DL_IDLE_STATE;
}

uint8_t
idle_handler(Datalink dl)
{
    return dl->state;
}

uint8_t
rx_handler(Datalink dl)
{
    return dl->state;
}

uint8_t
control_handler(Datalink dl)
{
    EXTRACT_PDU(dl->rx_pdu, dl->serial->serial_buffer);
    self.new_data = pdu_is_valid(dl->rx_pdu);
    return DL_IDLE_STATE;
}

uint8_t
tx_handler(Datalink dl)
{
    return 0;
}
