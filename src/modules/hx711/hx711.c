/**
  ******************************************************************************
  * @file   hx711.c
  * @author Jonathan Taylor
  * @date   3/22/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "hx711.h"
#include "peripherals.h"

struct hx711_t
{
    volatile bool pulse_due;

    volatile uint8_t pulse_count;

    uint8_t _count_to;

    volatile uint32_t values[10];
    volatile uint8_t  head;
    void * port;
    uint32_t    sck_pin;
    uint32_t    data_pin;
    Peripherals hal;
} self = {0};

static uint32_t v = 0;

void
hx711_cb()
{
    if (self.pulse_due) {
        if (self.pulse_count == 0) {
            if (!gpio_read_pin(self.hal->gpio, self.port, self.data_pin)) {
                gpio_set_pin(
                        self.hal->gpio, self.port,
                        self.sck_pin);
                if (self.pulse_count < 24) {
                    v <<= 1;
                }
                self.pulse_due = false;
            }
        } else {
            gpio_set_pin(
                    self.hal->gpio, self.port,
                    self.sck_pin);
            if (self.pulse_count < 24) {
                v <<= 1;
            }
            self.pulse_due = false;
        }

    } else {
        gpio_reset_pin(
                self.hal->gpio, self.port,
                self.sck_pin);
        if ((self.pulse_count < 24) &&
            gpio_read_pin(self.hal->gpio, self.port, self.data_pin)) {
            v++;
        }
        self.pulse_count++;
        self.pulse_due = true;
    }
    if (self.pulse_count > self._count_to) {

        self.values[self.head] = v ^ 0x800000;
        self.head        = (self.head + 1) % 10;
        self.pulse_due   = true;
        self.pulse_count = 0;
        v = 0;
    }
}

uint8_t
hx711_pulse_count(HX711 base)
{
    return base->pulse_count;
}

HX711
hx711_create(
        Peripherals hal, uint32_t sck_pin, uint32_t data_pin, void * port,
        void * tim_inst)
{
    self.pulse_count = 0;
    self._count_to   = 25;

    self.pulse_due = true;
    self.head      = 0;
    self.hal       = hal;
    self.sck_pin   = sck_pin;
    self.data_pin  = data_pin;
    self.port      = port;
    /* timer init */

    gpio_init_pin(hal->gpio, self.port, self.data_pin, GPIO_PIN_MODE_INPUT);
    gpio_init_pin(hal->gpio, self.port, self.sck_pin, GPIO_PIN_MODE_NORMAL);
    timer_set_timeout(self.hal->timer, tim_inst, 100);
    gpio_set_pin(self.hal->gpio, self.port, self.sck_pin);
    timer_start(self.hal->timer, tim_inst, 100000);
    while (timer_get_tick(self.hal->timer, tim_inst) < 60);
    gpio_reset_pin(self.hal->gpio, self.port, self.sck_pin);
    timer_stop(self.hal->timer, tim_inst);
    while (gpio_read_pin(self.hal->gpio, self.port, self.data_pin));
    timer_register_update_callback(self.hal->timer, tim_inst, hx711_cb);
    timer_set_timeout(self.hal->timer, tim_inst, 1);
    timer_start(self.hal->timer, tim_inst, 100000);
    return &self;
}

uint32_t hx711_read(HX711 base)
{
    uint32_t      ret = 0;
    for (uint16_t i   = 0; i < 10; i++) {
        ret += base->values[i];
    }
    return ret / 10;

}
