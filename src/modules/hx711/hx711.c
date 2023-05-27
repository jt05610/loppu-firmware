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

static struct hx711_t
{
    Peripherals hal;
    void * spiInst;
    uint8_t          readyPulse[1];
    uint8_t          clockPulses[7];
    volatile int32_t value;
} self = {
        .hal=0,
        .spiInst=0,
        .readyPulse={0x00},
        .clockPulses={0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xa8}
};

HX711
hx711_create(
        Peripherals hal, void * spi_inst)
{
    self.hal     = hal;
    self.spiInst = spi_inst;
    spi_open(hal->spi, spi_inst);
    hx711_reset(&self);
    return &self;
}

int32_t
get_bits(uint8_t buf2[7])
{
    unsigned char byte;
    int32_t       desired_bits;
    int           i, j;
    int           size = 6;
    desired_bits = 0;
    for (i       = 0; i <= size - 1; i++) {
        for (j = 6; j >= 0; j = j - 2) {
            byte         = buf2[i] & (1 << j);
            byte >>= j;
            desired_bits = desired_bits | byte;
            if (j > 0 | i < size - 1) {
                desired_bits = (desired_bits << 1);
            }
        }
    }
    return desired_bits;
}

void hx711_poll(HX711 base)
{
    uint8_t fstBuf[1];
    uint8_t rxBuf[7];
    spi_transact(base->hal->spi, base->spiInst, fstBuf, base->readyPulse, 1);
    if (fstBuf[0] == 0x00) {
        spi_transact(
                base->hal->spi, base->spiInst, rxBuf, base->clockPulses, 7);

        base->value = get_bits(rxBuf);
    }
}

int32_t
hx711_read(HX711 base)
{
    return base->value;
}

void hx711_reset(HX711 base)
{
    uint8_t       msg[1] = {0xFF};
    uint8_t       rx[1];
    for (uint16_t i      = 0; i < 500; i++) {
        spi_transact(base->hal->spi, base->spiInst, rx, msg, 1);
    }
}