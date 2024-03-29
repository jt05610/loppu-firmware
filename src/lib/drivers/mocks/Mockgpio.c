/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "Mockgpio.h"

static const char* CMockString_base = "base";
static const char* CMockString_gpio_read_pin = "gpio_read_pin";
static const char* CMockString_gpio_read_port = "gpio_read_port";
static const char* CMockString_gpio_reset_pin = "gpio_reset_pin";
static const char* CMockString_gpio_set_pin = "gpio_set_pin";
static const char* CMockString_gpio_toggle = "gpio_toggle";
static const char* CMockString_gpio_write_port = "gpio_write_port";
static const char* CMockString_pin = "pin";
static const char* CMockString_port = "port";
static const char* CMockString_value = "value";

typedef struct _CMOCK_gpio_set_pin_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  GPIO Expected_base;
  gpio_port_t Expected_port;
  gpio_pin_t Expected_pin;

} CMOCK_gpio_set_pin_CALL_INSTANCE;

typedef struct _CMOCK_gpio_reset_pin_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  GPIO Expected_base;
  gpio_port_t Expected_port;
  gpio_pin_t Expected_pin;

} CMOCK_gpio_reset_pin_CALL_INSTANCE;

typedef struct _CMOCK_gpio_read_port_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  uint32_t ReturnVal;
  GPIO Expected_base;
  gpio_port_t Expected_port;

} CMOCK_gpio_read_port_CALL_INSTANCE;

typedef struct _CMOCK_gpio_read_pin_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  uint8_t ReturnVal;
  GPIO Expected_base;
  gpio_port_t Expected_port;
  gpio_pin_t Expected_pin;

} CMOCK_gpio_read_pin_CALL_INSTANCE;

typedef struct _CMOCK_gpio_write_port_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  GPIO Expected_base;
  gpio_port_t Expected_port;
  uint32_t Expected_value;

} CMOCK_gpio_write_port_CALL_INSTANCE;

typedef struct _CMOCK_gpio_toggle_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  GPIO Expected_base;
  gpio_port_t Expected_port;
  gpio_pin_t Expected_pin;

} CMOCK_gpio_toggle_CALL_INSTANCE;

static struct MockgpioInstance
{
  CMOCK_MEM_INDEX_TYPE gpio_set_pin_CallInstance;
  CMOCK_MEM_INDEX_TYPE gpio_reset_pin_CallInstance;
  CMOCK_MEM_INDEX_TYPE gpio_read_port_CallInstance;
  CMOCK_MEM_INDEX_TYPE gpio_read_pin_CallInstance;
  CMOCK_MEM_INDEX_TYPE gpio_write_port_CallInstance;
  CMOCK_MEM_INDEX_TYPE gpio_toggle_CallInstance;
} Mock;

extern jmp_buf AbortFrame;

void Mockgpio_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.gpio_set_pin_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_gpio_set_pin);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  call_instance = Mock.gpio_reset_pin_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_gpio_reset_pin);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  call_instance = Mock.gpio_read_port_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_gpio_read_port);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  call_instance = Mock.gpio_read_pin_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_gpio_read_pin);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  call_instance = Mock.gpio_write_port_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_gpio_write_port);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  call_instance = Mock.gpio_toggle_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_gpio_toggle);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
}

void Mockgpio_Init(void)
{
  Mockgpio_Destroy();
}

void Mockgpio_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

void gpio_set_pin(GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_gpio_set_pin_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_gpio_set_pin);
  cmock_call_instance = (CMOCK_gpio_set_pin_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.gpio_set_pin_CallInstance);
  Mock.gpio_set_pin_CallInstance = CMock_Guts_MemNext(Mock.gpio_set_pin_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_gpio_set_pin,CMockString_base);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_base), (void*)(&base), sizeof(GPIO), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_set_pin,CMockString_port);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_port), (void*)(&port), sizeof(gpio_port_t), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_set_pin,CMockString_pin);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin), sizeof(gpio_pin_t), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_gpio_set_pin(CMOCK_gpio_set_pin_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, gpio_pin_t pin);
void CMockExpectParameters_gpio_set_pin(CMOCK_gpio_set_pin_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  memcpy((void*)(&cmock_call_instance->Expected_base), (void*)(&base),
         sizeof(GPIO[sizeof(base) == sizeof(GPIO) ? 1 : -1])); /* add GPIO to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_port), (void*)(&port),
         sizeof(gpio_port_t[sizeof(port) == sizeof(gpio_port_t) ? 1 : -1])); /* add gpio_port_t to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin),
         sizeof(gpio_pin_t[sizeof(pin) == sizeof(gpio_pin_t) ? 1 : -1])); /* add gpio_pin_t to :treat_as_array if this causes an error */
}

void gpio_set_pin_CMockExpect(UNITY_LINE_TYPE cmock_line, GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpio_set_pin_CALL_INSTANCE));
  CMOCK_gpio_set_pin_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpio_set_pin_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpio_set_pin_CallInstance = CMock_Guts_MemChain(Mock.gpio_set_pin_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_gpio_set_pin(cmock_call_instance, base, port, pin);
}

void gpio_reset_pin(GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_gpio_reset_pin_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_gpio_reset_pin);
  cmock_call_instance = (CMOCK_gpio_reset_pin_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.gpio_reset_pin_CallInstance);
  Mock.gpio_reset_pin_CallInstance = CMock_Guts_MemNext(Mock.gpio_reset_pin_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_gpio_reset_pin,CMockString_base);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_base), (void*)(&base), sizeof(GPIO), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_reset_pin,CMockString_port);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_port), (void*)(&port), sizeof(gpio_port_t), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_reset_pin,CMockString_pin);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin), sizeof(gpio_pin_t), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_gpio_reset_pin(CMOCK_gpio_reset_pin_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, gpio_pin_t pin);
void CMockExpectParameters_gpio_reset_pin(CMOCK_gpio_reset_pin_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  memcpy((void*)(&cmock_call_instance->Expected_base), (void*)(&base),
         sizeof(GPIO[sizeof(base) == sizeof(GPIO) ? 1 : -1])); /* add GPIO to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_port), (void*)(&port),
         sizeof(gpio_port_t[sizeof(port) == sizeof(gpio_port_t) ? 1 : -1])); /* add gpio_port_t to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin),
         sizeof(gpio_pin_t[sizeof(pin) == sizeof(gpio_pin_t) ? 1 : -1])); /* add gpio_pin_t to :treat_as_array if this causes an error */
}

void gpio_reset_pin_CMockExpect(UNITY_LINE_TYPE cmock_line, GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpio_reset_pin_CALL_INSTANCE));
  CMOCK_gpio_reset_pin_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpio_reset_pin_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpio_reset_pin_CallInstance = CMock_Guts_MemChain(Mock.gpio_reset_pin_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_gpio_reset_pin(cmock_call_instance, base, port, pin);
}

uint32_t gpio_read_port(GPIO base, gpio_port_t port)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_gpio_read_port_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_gpio_read_port);
  cmock_call_instance = (CMOCK_gpio_read_port_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.gpio_read_port_CallInstance);
  Mock.gpio_read_port_CallInstance = CMock_Guts_MemNext(Mock.gpio_read_port_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_gpio_read_port,CMockString_base);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_base), (void*)(&base), sizeof(GPIO), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_read_port,CMockString_port);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_port), (void*)(&port), sizeof(gpio_port_t), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_gpio_read_port(CMOCK_gpio_read_port_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port);
void CMockExpectParameters_gpio_read_port(CMOCK_gpio_read_port_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port)
{
  memcpy((void*)(&cmock_call_instance->Expected_base), (void*)(&base),
         sizeof(GPIO[sizeof(base) == sizeof(GPIO) ? 1 : -1])); /* add GPIO to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_port), (void*)(&port),
         sizeof(gpio_port_t[sizeof(port) == sizeof(gpio_port_t) ? 1 : -1])); /* add gpio_port_t to :treat_as_array if this causes an error */
}

void gpio_read_port_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, GPIO base, gpio_port_t port, uint32_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpio_read_port_CALL_INSTANCE));
  CMOCK_gpio_read_port_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpio_read_port_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpio_read_port_CallInstance = CMock_Guts_MemChain(Mock.gpio_read_port_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_gpio_read_port(cmock_call_instance, base, port);
  cmock_call_instance->ReturnVal = cmock_to_return;
}

uint8_t gpio_read_pin(GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_gpio_read_pin_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_gpio_read_pin);
  cmock_call_instance = (CMOCK_gpio_read_pin_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.gpio_read_pin_CallInstance);
  Mock.gpio_read_pin_CallInstance = CMock_Guts_MemNext(Mock.gpio_read_pin_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_gpio_read_pin,CMockString_base);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_base), (void*)(&base), sizeof(GPIO), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_read_pin,CMockString_port);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_port), (void*)(&port), sizeof(gpio_port_t), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_read_pin,CMockString_pin);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin), sizeof(gpio_pin_t), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_gpio_read_pin(CMOCK_gpio_read_pin_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, gpio_pin_t pin);
void CMockExpectParameters_gpio_read_pin(CMOCK_gpio_read_pin_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  memcpy((void*)(&cmock_call_instance->Expected_base), (void*)(&base),
         sizeof(GPIO[sizeof(base) == sizeof(GPIO) ? 1 : -1])); /* add GPIO to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_port), (void*)(&port),
         sizeof(gpio_port_t[sizeof(port) == sizeof(gpio_port_t) ? 1 : -1])); /* add gpio_port_t to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin),
         sizeof(gpio_pin_t[sizeof(pin) == sizeof(gpio_pin_t) ? 1 : -1])); /* add gpio_pin_t to :treat_as_array if this causes an error */
}

void gpio_read_pin_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, GPIO base, gpio_port_t port, gpio_pin_t pin, uint8_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpio_read_pin_CALL_INSTANCE));
  CMOCK_gpio_read_pin_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpio_read_pin_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpio_read_pin_CallInstance = CMock_Guts_MemChain(Mock.gpio_read_pin_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_gpio_read_pin(cmock_call_instance, base, port, pin);
  cmock_call_instance->ReturnVal = cmock_to_return;
}

void gpio_write_port(GPIO base, gpio_port_t port, uint32_t value)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_gpio_write_port_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_gpio_write_port);
  cmock_call_instance = (CMOCK_gpio_write_port_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.gpio_write_port_CallInstance);
  Mock.gpio_write_port_CallInstance = CMock_Guts_MemNext(Mock.gpio_write_port_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_gpio_write_port,CMockString_base);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_base), (void*)(&base), sizeof(GPIO), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_write_port,CMockString_port);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_port), (void*)(&port), sizeof(gpio_port_t), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_write_port,CMockString_value);
    UNITY_TEST_ASSERT_EQUAL_HEX32(cmock_call_instance->Expected_value, value, cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_gpio_write_port(CMOCK_gpio_write_port_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, uint32_t value);
void CMockExpectParameters_gpio_write_port(CMOCK_gpio_write_port_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, uint32_t value)
{
  memcpy((void*)(&cmock_call_instance->Expected_base), (void*)(&base),
         sizeof(GPIO[sizeof(base) == sizeof(GPIO) ? 1 : -1])); /* add GPIO to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_port), (void*)(&port),
         sizeof(gpio_port_t[sizeof(port) == sizeof(gpio_port_t) ? 1 : -1])); /* add gpio_port_t to :treat_as_array if this causes an error */
  cmock_call_instance->Expected_value = value;
}

void gpio_write_port_CMockExpect(UNITY_LINE_TYPE cmock_line, GPIO base, gpio_port_t port, uint32_t value)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpio_write_port_CALL_INSTANCE));
  CMOCK_gpio_write_port_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpio_write_port_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpio_write_port_CallInstance = CMock_Guts_MemChain(Mock.gpio_write_port_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_gpio_write_port(cmock_call_instance, base, port, value);
}

void gpio_toggle(GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_gpio_toggle_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_gpio_toggle);
  cmock_call_instance = (CMOCK_gpio_toggle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.gpio_toggle_CallInstance);
  Mock.gpio_toggle_CallInstance = CMock_Guts_MemNext(Mock.gpio_toggle_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_gpio_toggle,CMockString_base);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_base), (void*)(&base), sizeof(GPIO), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_toggle,CMockString_port);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_port), (void*)(&port), sizeof(gpio_port_t), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_gpio_toggle,CMockString_pin);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin), sizeof(gpio_pin_t), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
}

void CMockExpectParameters_gpio_toggle(CMOCK_gpio_toggle_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, gpio_pin_t pin);
void CMockExpectParameters_gpio_toggle(CMOCK_gpio_toggle_CALL_INSTANCE* cmock_call_instance, GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  memcpy((void*)(&cmock_call_instance->Expected_base), (void*)(&base),
         sizeof(GPIO[sizeof(base) == sizeof(GPIO) ? 1 : -1])); /* add GPIO to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_port), (void*)(&port),
         sizeof(gpio_port_t[sizeof(port) == sizeof(gpio_port_t) ? 1 : -1])); /* add gpio_port_t to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_pin), (void*)(&pin),
         sizeof(gpio_pin_t[sizeof(pin) == sizeof(gpio_pin_t) ? 1 : -1])); /* add gpio_pin_t to :treat_as_array if this causes an error */
}

void gpio_toggle_CMockExpect(UNITY_LINE_TYPE cmock_line, GPIO base, gpio_port_t port, gpio_pin_t pin)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_gpio_toggle_CALL_INSTANCE));
  CMOCK_gpio_toggle_CALL_INSTANCE* cmock_call_instance = (CMOCK_gpio_toggle_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.gpio_toggle_CallInstance = CMock_Guts_MemChain(Mock.gpio_toggle_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_gpio_toggle(cmock_call_instance, base, port, pin);
}

