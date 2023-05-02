/**
  ******************************************************************************
  * @file   property.c
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

#include <string.h>
#include "property.h"

void property_set_bool(Property property, bool value)
{
    property->value.type     = Bool;
    property->value.val.int8 = value;
}

void property_set_int(Property property, int value)
{

    property->value.type      = Int;
    property->value.val.int32 = value;
}

void property_set_int8(Property property, int8_t value)
{
    property->value.type     = Int8;
    property->value.val.int8 = value;
}

void property_set_int16(Property property, int16_t value)
{
    property->value.type      = Int16;
    property->value.val.int16 = value;
}

void property_set_int32(Property property, int32_t value)
{
    property->value.type      = Int32;
    property->value.val.int32 = value;
}

void property_set_uint8(Property property, uint8_t value)
{
    property->value.type      = Uint8;
    property->value.val.uint8 = value;
}

void property_set_uint16(Property property, uint16_t value)
{
    property->value.type       = Uint16;
    property->value.val.uint16 = value;
}

void property_set_uint32(Property property, uint32_t value)
{
    property->value.type       = Uint32;
    property->value.val.uint32 = value;
}

void property_set_string(Property property, const char * value)
{
    property->value.type       = String;
    property->value.val.string = strdup(value);
}

bool property_get_bool(Property property, bool * value)
{
    if (property->value.type != Bool) {
        return false;
    }
    *value = property->value.val.boolean;
    return true;
}

bool property_get_int(Property property, int * value)
{
    if (property->value.type != Int) {
        return false;
    }
    *value = property->value.val.int32;
    return true;
}

bool property_get_int8(const Property property, int8_t * value)
{
    if (property->value.type != Int8) {
        return false;
    }
    *value = property->value.val.int8;
    return true;
}

bool property_get_int16(const Property property, int16_t * value)
{
    if (property->value.type != Int16) {
        return false;
    }
    *value = property->value.val.int16;
    return true;
}

bool property_get_int32(const Property property, int32_t * value)
{
    if (property->value.type != Int32) {
        return false;
    }
    *value = property->value.val.int32;
    return true;
}

bool property_get_uint8(const Property property, uint8_t * value)
{
    if (property->value.type != Uint8) {
        return false;
    }
    *value = property->value.val.uint8;
    return true;
}

bool property_get_uint16(const Property property, uint16_t * value)
{
    if (property->value.type != Uint16) {
        return false;
    }
    *value = property->value.val.uint16;
    return true;
}

bool property_get_uint32(const Property property, uint32_t * value)
{
    if (property->value.type != Uint32) {
        return false;
    }
    *value = property->value.val.uint32;
    return true;
}

bool property_get_string(const Property property, char ** value)
{
    if (property->value.type != String) {
        return false;
    }
    *value = strdup(property->value.val.string);
    return true;
}