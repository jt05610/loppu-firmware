//
// Created by Jonathan Taylor on 5/25/22.
//

#ifndef MICROFLUIDICSYSTEM_PDU_TYPES_H
#define MICROFLUIDICSYSTEM_PDU_TYPES_H

#include "project_types.h"
#include "crc.h"

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
    for (size_t i      = pdu->data.size; i > 0; i--) {
        pdu->data.bytes[i] = pdu->data.bytes[i - 1];
    }
    pdu->data.bytes[0] = pdu->func_code;
    sized_array_create(pdu->data.bytes, pdu->data.size + 1, dest);
}

static inline void
serialize_serial_pdu(SerialPDU data, sized_array_t * dest)
{
    dest->bytes    = data->pdu->data.bytes;
    for (size_t i  = data->pdu->data.size; i > 0; i--) {
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
    if (pos == pdu->pdu->data.size) {
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

#define EXTRACT_PDU(dest, src, n)                          \
    (dest)->pdu->data.size = (n) - 4;                      \
    for (uint16_t i = 0; i < (n); i ++)                     \
        process_byte((dest), (src)[i])


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
            ) {
        if (equal_sized_array(&first->pdu->data, &second->pdu->data)) {
            ret = true;
        }
    }
    return ret;
}

static inline uint16_t
pdu_crc16(uint8_t address, ModbusPDU pdu)
{
    sized_array_t array;
    array.size = pdu->data.size + 2;
    static uint8_t bytes[256];
    bytes[0] = address;
    bytes[1] = pdu->func_code;
    for (size_t i = 2; i < array.size; i++) {
        bytes[i] = pdu->data.bytes[i - 2];
    }
    sized_array_create(bytes, array.size, &array);
    return crc16(&array);
}

static inline bool
pdu_is_valid(SerialPDU pdu)
{
    return pdu_crc16(pdu->address, pdu->pdu) == pdu->crc;
}

static inline void
pdu_format(uint8_t address, ModbusPDU pdu, SerialPDU dest)
{
    create_serial_pdu(address, pdu, pdu_crc16(address, pdu), dest);
}

#endif //MICROFLUIDICSYSTEM_PDU_TYPES_H
