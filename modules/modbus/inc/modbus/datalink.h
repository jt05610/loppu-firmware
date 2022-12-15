//
// Created by Jonathan Taylor on 5/19/22.
//

/* TODO
 * implement ascii
 * figure out if dl_update_t is needed
 * implement rest of counters
 */

#ifndef MICROFLUIDICSYSTEM_DATALINK_H
#define MICROFLUIDICSYSTEM_DATALINK_H

#include <stdint.h>
#include "types.h"

#define ERROR_COUNTERS 8


typedef struct datalink_t           * Datalink;
typedef struct datalink_interface_t * DatalinkInterface;

typedef enum dl_update_t
{
    ReceivedUnicast,
    ReceivedBroadcast,
    None,
    ResponseTimeout,
    FrameError,
}                                   dl_update_t;

typedef enum dl_counter_t
{
    BusMessageCount            = 0x0B,
    BusCommunicationErrorCount = 0x0C,
    BusExceptionErrorCount     = 0x0D,
    ServerMessageCount         = 0x0E,
    ServerNoResponseCount      = 0x0F,
    ServerNAKCount             = 0x10,
    ServerBusyCount            = 0x11,
    BusCharacterOverrunCount   = 0x12
}                                   dl_counter_t;

dl_update_t dl_update(Datalink base);

void dl_format_pdu(uint8_t address, ModbusPDU pdu, SerialPDU dest);

void dl_transmit(Datalink base, SerialPDU pdu);

void dl_handle_error(Datalink base);

bool dl_crc_check(SerialPDU pdu);

dl_update_t dl_receive(Datalink base, SerialPDU data);

uint16_t dl_crc16(uint8_t address, ModbusPDU pdu);

#include "datalink_private.h"

#endif //MICROFLUIDICSYSTEM_DATALINK_H
