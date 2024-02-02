/**
  ******************************************************************************
  * @file   data_model.h
  * @author Jonathan Taylor
  * @date   12/4/22
  * @brief  DataModel abstraction layer header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_DATA_MODEL_H
#define INJECTOR_DATA_MODEL_H
/**
 * @addtogroup Modbus
 * @{
 */

/**
 * @defgroup DataModel
 * @brief Data model abstraction layer
 * @{
 */

#include "primary_table.h"
#include "pdu_types.h"

/**
 * @brief tables
 * @defgroup ModbusTables
 * @{
 */
#define DI_TABLE    0x00    /**< @brief Discrete inputs table */
#define COIL_TABLE  0x01    /**< @brief Coils table */
#define IR_TABLE    0x02    /**< @brief Input registers table */
#define HR_TABLE    0x03    /**< @brief Holding registers table */
/** @} */

typedef struct data_model_t *DataModel;


typedef struct device_info_t {
    char *vendor_name;
    char *product_code;
    char *major_minor_revision;
    char *vendor_url;
    char *product_name;
    char *model_name;
    char *user_application_name;
    char *device_schema;
    const char *serial_number;
} device_info_t;

/**
 * @brief Data model structure
 */
typedef struct data_model_t {
    void *device;
    primary_table_t *tables; /**< @brief One for each @ref ModbusTables */
    device_info_t *info;
} data_model_t;

/**
 * @brief Creates a datamodel to access the passed @ref PrimaryTable.
 * @param tables Tables unique to device.
 * @param device_info Device information.
 * @return Pointer to instantiated data model.
 */
DataModel datamodel_create(PrimaryTable tables, device_info_t *device_info);

/**
 * @brief Processes received @ref ModbusPDU
 * @param base DataModel instance
 * @param pdu Request structure
 */
void datamodel_handle(DataModel base, ModbusPDU pdu);

/** @} */

/** @} */

#endif //INJECTOR_DATA_MODEL_H
