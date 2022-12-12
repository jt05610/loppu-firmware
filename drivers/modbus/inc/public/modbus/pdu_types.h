//
// Created by Jonathan Taylor on 5/25/22.
//

#ifndef MICROFLUIDICSYSTEM_PDU_TYPES_H
#define MICROFLUIDICSYSTEM_PDU_TYPES_H

#include "project_types.h"

typedef struct modbus_pdu_t * ModbusPDU;
typedef struct serial_pdu_t * SerialPDU;

typedef struct modbus_pdu_t
{
    uint8_t       func_code;
    sized_array_t data;

} modbus_pdu_t;

typedef struct serial_pdu_t
{
    uint8_t   address;
    ModbusPDU pdu;
    uint16_t  crc;
} serial_pdu_t;

static inline void
create_modbus_pdu(uint8_t f_code, uint8_t * data, size_t size, ModbusPDU dest)
{
    dest->func_code = f_code;
    sized_array_create(data, size, &dest->data);
}

static inline void
create_serial_pdu(uint8_t addr, ModbusPDU pdu, uint16_t crc, SerialPDU dest)
{
    dest->address = addr;
    dest->pdu     = pdu;
    dest->crc     = crc;
}

static inline void
serialize_modbus_pdu(ModbusPDU pdu, sized_array_t * dest)
{
    for (size_t i      = pdu->data.size; i > 0; i--)
    {
        pdu->data.bytes[i] = pdu->data.bytes[i - 1];
    }
    pdu->data.bytes[0] = pdu->func_code;
    sized_array_create(pdu->data.bytes, pdu->data.size + 1, dest);
}

static inline void
serialize_serial_pdu(SerialPDU data, sized_array_t * dest)
{
    dest->bytes    = data->pdu->data.bytes;
    for (size_t i  = data->pdu->data.size; i > 0; i--)
    {
        dest->bytes[i + 1] = dest->bytes[i - 1];
    }
    dest->bytes[0] = data->address;
    dest->bytes[1] = data->pdu->func_code;
    dest->size = data->pdu->data.size + 4;
    dest->bytes[dest->size - 2] = *((uint8_t *) &(data->crc) + 0);
    dest->bytes[dest->size - 1] = *((uint8_t *) &(data->crc) + 1);
}

static inline uint8_t
extract_address(SerialPDU pdu, uint8_t byte)
{
    pdu->address = byte;
    return 1;
}

static inline uint8_t
extract_func_code(SerialPDU pdu, uint8_t byte)
{
    pdu->pdu->func_code = byte;
    return 2;
}

static inline uint8_t
extract_data(SerialPDU pdu, uint8_t byte)
{
    uint8_t         ret = 2;
    static uint16_t pos = 0;
    pdu->pdu->data.bytes[pos++] = byte;
    if (pos == pdu->pdu->data.size)
    {
        ret = 3;
        pos = 0;
    }

    return ret;
}

static inline uint8_t
extract_crc_first(SerialPDU pdu, uint8_t byte)
{
    pdu->crc = byte;
    return 4;
}

static inline uint8_t
extract_crc_second(SerialPDU pdu, uint8_t byte)
{
    pdu->crc += 256U * byte;
    return 0;
}

typedef uint8_t (* extractor)(SerialPDU, uint8_t byte);

static inline void
process_byte(SerialPDU pdu, uint8_t byte)
{
    static uint8_t state = 0;

    static extractor extractors[5] = {
            extract_address,
            extract_func_code,
            extract_data,
            extract_crc_first,
            extract_crc_second,
    };
    state = extractors[state](pdu, byte);
}

static inline uint16_t
extract_pdu(uint8_t * buffer, uint16_t start, uint16_t size, SerialPDU pdu)
{
    static bool recurse = false;
    uint16_t go_to = start + size;
    uint16_t remaining = 0;
    if (!recurse)
        pdu->pdu->data.size = size - 4;
    else
        recurse = false;
    if (go_to >= RX_BUFFER_SIZE)
    {
        remaining = go_to - RX_BUFFER_SIZE;
        go_to     = RX_BUFFER_SIZE;
        recurse = true;
    }

    for (uint16_t i = start; i < go_to; i++)
    {
        process_byte(pdu, buffer[i]);
    }
    if (recurse)
    {
        go_to = extract_pdu(buffer, 0, remaining, pdu);
    }
    return go_to;
}

static inline void
deserialize_pdu(sized_array_t * array, SerialPDU pdu)
{
    pdu->address        = *array->bytes++;
    pdu->pdu->func_code = *array->bytes++;
    pdu->crc            = 256U * array->bytes[array->size - 3]
                          + array->bytes[array->size - 4];
    create_modbus_pdu(
            pdu->pdu->func_code, array->bytes, array->size - 4, pdu->pdu
    );
}


static inline bool
equal_serial_pdu(SerialPDU first, SerialPDU second)
{
    bool ret = false;
    if (first->address == second->address
        && first->crc == second->crc
        && first->pdu->func_code == second->pdu->func_code
            )
    {
        if (equal_sized_array(&first->pdu->data, &second->pdu->data))
        {
            ret = true;
        }
    }
    return ret;
}

#endif //MICROFLUIDICSYSTEM_PDU_TYPES_H
