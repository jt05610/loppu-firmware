#include <gtest/gtest.h>

extern "C" {
#include "property.h"
}

TEST(PropertyTest, Bool)
{
    prop_t prop;
    bool   value = false;

    property_set_bool(&prop, value);

    bool result;
    bool success = property_get_bool(&prop, &result);
    ASSERT_TRUE(success);
    ASSERT_EQ(result, value);
}

TEST(PropertyTest, Int)
{
    prop_t prop;
    int    value = 42;

    property_set_int(&prop, value);

    int  result;
    bool success = property_get_int(&prop, &result);
    ASSERT_TRUE(success);
    ASSERT_EQ(result, value);
}


TEST(PropertyTest, String)
{
    prop_t prop;
    const char *    value = "foobar";

    property_set_string(&prop, value);

    char *  result;
    bool success = property_get_string(&prop, &result);
    ASSERT_TRUE(success);
    ASSERT_STREQ(result, value);
}

TEST(PropertyTest, Int8)
{
    prop_t prop;
    int8_t    value = 42;

    property_set_int8(&prop, value);

    int8_t  result;
    bool success = property_get_int8(&prop, &result);
    ASSERT_TRUE(success);
    ASSERT_EQ(result, value);
}

TEST(PropertyTest, Int16)
{
    prop_t prop;
    int16_t    value = 42;

    property_set_int16(&prop, value);

    int16_t  result;
    bool success = property_get_int16(&prop, &result);
    ASSERT_TRUE(success);
    ASSERT_EQ(result, value);
}

TEST(PropertyTest, Int32)
{
    prop_t prop;
    int32_t    value = 42;

    property_set_int32(&prop, value);

    int32_t  result;
    bool success = property_get_int32(&prop, &result);
    ASSERT_TRUE(success);
    ASSERT_EQ(result, value);
}

TEST(PropertyTest, Uint8)
{
    prop_t prop;
    uint8_t    value = 42;

    property_set_uint8(&prop, value);

    uint8_t  result;
    bool success = property_get_uint8(&prop, &result);
    ASSERT_TRUE(success);
    ASSERT_EQ(result, value);
}

TEST(PropertyTest, Uint16)
{
    prop_t prop;
    uint16_t    value = 42;

    property_set_uint16(&prop, value);

    uint16_t  result;
    bool success = property_get_uint16(&prop, &result);
    ASSERT_TRUE(success);
    ASSERT_EQ(result, value);
}

TEST(PropertyTest, Uint32)
{
    prop_t prop;
    uint32_t    value = 42;

    property_set_uint32(&prop, value);

    uint32_t  result;
    bool success = property_get_uint32(&prop, &result);
    ASSERT_TRUE(success);
    ASSERT_EQ(result, value);
}
