/**
  ******************************************************************************
  * @file   property.h
  * @author Jonathan Taylor
  * @date   5/2/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_PROPERTY_H
#define INJECTOR_PROPERTY_H

#include <stdbool.h>
#include <stdint.h>
#include "token.h"

typedef struct prop_t * Property;

typedef enum prop_type_t
{
    Bool,
    Int,
    Int8,
    Int16,
    Int32,
    Uint8,
    Uint16,
    Uint32,
    String,

} prop_type_t;

typedef union val_t
{
    bool     boolean;
    int8_t   int8;
    int16_t  int16;
    int32_t  int32;
    uint8_t  uint8;
    uint16_t uint16;
    uint32_t uint32;
    const char * string;
} val_t;

typedef struct typed_val_t
{
    prop_type_t type;
    val_t       val;
} typed_val_t;

typedef struct prop_t
{
    token       pkey;
    typed_val_t value;
} prop_t;

void property_set_bool(Property property, bool value);

void property_set_int(Property property, int value);

void property_set_int8(Property property, int8_t value);

void property_set_int16(Property property, int16_t value);

void property_set_int32(Property property, int32_t value);

void property_set_uint8(Property property, uint8_t value);

void property_set_uint16(Property property, uint16_t value);

void property_set_uint32(Property property, uint32_t value);

void property_set_string(Property property, const char * value);

bool property_get_bool(Property property, bool * value);

bool property_get_int(Property property, int * value);

bool property_get_int8(Property property, int8_t * value);

bool property_get_int16(Property property, int16_t * value);

bool property_get_int32(Property property, int32_t * value);

bool property_get_uint8(Property property, uint8_t * value);

bool property_get_uint16(Property property, uint16_t * value);

bool property_get_uint32(Property property, uint32_t * value);

bool property_get_string(Property property, char ** value);

#endif //INJECTOR_PROPERTY_H
