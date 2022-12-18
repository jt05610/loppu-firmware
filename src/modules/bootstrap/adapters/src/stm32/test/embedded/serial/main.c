/**
  ******************************************************************************
  * @file   runner.c
  * @author Jonathan Taylor
  * @date   12/13/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32g031xx.h"
#include "stm32g0xx/stm32_clock.h"
#include "test_serial.h"
#include "test_modbus.h"
#include "peripherals.h"
#include "fake_device.h"

static Serial instance = {0};


static peripherals_t p;
static FakeDevice device;

void rx_callback(void * data, uint16_t n_received);

static inline void
_write(void *d, uint8_t * bytes, uint16_t data)
{
    serial_write(p.serial, d, bytes, data);
}

int
main()
{
    stm32_serial_set_rto_cb(USART1, rx_callback, USART1);
    p.serial = stm32_serial_create();

    app_init_t params = {
            .rx_buffer=p.serial->rx_buffer,
            .write_handler=_write,
            .serial_device=USART1,
            .restart=0,
            .address=0x01,
    };
    stm32_clock_config();

    device = fake_device_create(&p, &params);
    serial_open(p.serial, USART1);
    while (1) {
        fake_device_run(device);
    }
}

void rx_callback(void * data, uint16_t n_received)
{
    server_new_data_handler(n_received);
}
