//
// Created by Jonathan Taylor on 5/19/22.
//
#include "datalink.h"
#include "crc.h"

void
dl_transmit(Datalink base, SerialPDU pdu)
{
    sized_array_t to_send;
    serialize_serial_pdu(pdu, &to_send);
    base->vtable->write_handler(base->serial_device, to_send.bytes, to_send.size);
    deserialize_pdu(&to_send, pdu);
}


dl_update_t
dl_receive(Datalink base, SerialPDU data)
{
    static dl_update_t ret = None;
    base->current_pos = extract_pdu(base->buffer, base->current_pos, base->target_pos, data);
    ret = (data->address == 0x00) ? ReceivedBroadcast : ReceivedUnicast;
    return ret;
}

dl_update_t
dl_update(Datalink base)
{
    static dl_update_t ret = None;
    if (base && base->vtable && base->vtable->update)
    {
        ret = base->vtable->update();
    }
    return ret;
}

void
dl_handle_error(Datalink base)
{
    if (base && base->vtable && base->vtable->handle_error)
    {
        base->vtable->handle_error();
    }
}

bool
dl_crc_check(SerialPDU pdu)
{
    return dl_crc16(pdu->address, pdu->pdu) == pdu->crc;
}

uint16_t
dl_crc16(uint8_t address, ModbusPDU pdu)
{
    sized_array_t array;
    array.size = pdu->data.size + 2;
    static uint8_t bytes[256];
    bytes[0] = address;
    bytes[1] = pdu->func_code;
    for (size_t i = 2; i < array.size; i++)
        bytes[i]  = pdu->data.bytes[i - 2];
    sized_array_create(bytes, array.size, &array);
    return crc16(&array);
}

void
dl_format_pdu(uint8_t address, ModbusPDU pdu, SerialPDU dest)
{
    create_serial_pdu(address, pdu, dl_crc16(address, pdu), dest);
}