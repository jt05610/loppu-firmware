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
        Peripherals hal, void * spi_inst, void * tim_inst,
        uint32_t update_freq);

int32_t hx711_read(HX711 base);

void hx711_start(HX711 base);

void hx711_stop(HX711 base);

bool hx711_poll(HX711 base);

void hx711_reset(HX711 base);


#endif //INJECTOR_HX711_H
