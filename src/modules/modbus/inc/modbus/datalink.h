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

/**
 * @defgroup Datalink
 * @ingroup Modbus
 * @{
 */
#include <stdint.h>
#include "types.h"
#include "serial.h"
#include "timer.h"

#define ERROR_COUNTERS 8

/**
 * @brief pointer to instantiated datalink
 */
typedef struct datalink_t * Datalink;

/**
 * @defgroup Datalink_update Datalink states
 * @{
 */
#define DL_INITIAL_STATE    0xFF
#define DL_IDLE_STATE       0x00
#define DL_RX_STATE         0x01
#define DL_CONTROL_STATE    0x02
#define DL_TX_STATE         0x03

/** @} */

#define DL_BusMessageCount             0x0B
#define DL_BusCommunicationErrorCount  0x0C
#define DL_BusExceptionErrorCount      0x0D
#define DL_ServerMessageCount          0x0E
#define DL_ServerNoResponseCount       0x0F
#define DL_ServerNAKCount              0x10
#define DL_ServerBusyCount             0x11
#define DL_BusCharacterOverrunCount    0x12

/**
 * @brief creates datalink
 * @param serial_instance which serial device to read and write data to/from
 * @return Pointer to instantiated datalink
 */
Datalink
dl_create(Serial serial, Timer timer, void * ser_inst, void * tim_inst);

/**
 * @brief Processes new data
 * @param base
 * @return
 */
uint8_t dl_update(Datalink base);

bool dl_new_data(Datalink base);

void dl_reset(Datalink base);

ModbusPDU dl_rx_pdu(Datalink base);

void dl_send(Datalink base, ModbusPDU pdu);

#include "datalink_private.h"

/** @} */

#endif //MICROFLUIDICSYSTEM_DATALINK_H
