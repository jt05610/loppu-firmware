/**
  ******************************************************************************
  * @file   hx711.h
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

#ifndef INJECTOR_HX711_H
#define INJECTOR_HX711_H

#include <stdint.h>
#include <stdbool.h>
#include "spi.h"
#include "peripherals.h"

typedef struct hx711_t * HX711;

HX711 hx711_create(
        Peripherals hal, uint32_t sck_pin, uint32_t data_pin, void * port,
        void * tim_inst);

void hx711_run(HX711 base, uint8_t n_pulses);

uint32_t hx711_read(HX711 base);

void hx711_cb();

uint8_t hx711_pulse_count(HX711 base);

#endif //INJECTOR_HX711_H
