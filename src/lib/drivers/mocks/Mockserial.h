/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCKSERIAL_H
#define _MOCKSERIAL_H

#include "unity.h"
#include "serial.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

#ifdef __cplusplus
extern "C" {
#endif

void Mockserial_Init(void);
void Mockserial_Destroy(void);
void Mockserial_Verify(void);




#define serial_open_Expect(base) serial_open_CMockExpect(__LINE__, base)
void serial_open_CMockExpect(UNITY_LINE_TYPE cmock_line, Serial base);
#define serial_close_Expect(base) serial_close_CMockExpect(__LINE__, base)
void serial_close_CMockExpect(UNITY_LINE_TYPE cmock_line, Serial base);
#define serial_read_ExpectAndReturn(base, dest, cmock_retval) serial_read_CMockExpectAndReturn(__LINE__, base, dest, cmock_retval)
void serial_read_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, Serial base, uint8_t* dest, uint16_t cmock_to_return);
#define serial_write_Expect(base, data, size) serial_write_CMockExpect(__LINE__, base, data, size)
void serial_write_CMockExpect(UNITY_LINE_TYPE cmock_line, Serial base, uint8_t* data, uint16_t size);
#define serial_attach_buffer_Expect(base, buffer, size) serial_attach_buffer_CMockExpect(__LINE__, base, buffer, size)
void serial_attach_buffer_CMockExpect(UNITY_LINE_TYPE cmock_line, Serial base, uint8_t* buffer, uint16_t size);

#ifdef __cplusplus
}
#endif

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
