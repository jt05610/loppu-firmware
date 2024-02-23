/**
  ******************************************************************************
  * @file   stm32_spi.c
  * @author Jonathan Taylor
  * @date   22 Mar 2023
  * @brief  STM32G031xx SPI header
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32_spi.h"

#include "stm32g0xx_ll_spi.h"
#include "spi_config.h"

static struct {
    spi_t base;
} self = {0};

static inline void spi_init();

static inline void open(void *instance);

static inline void close(void *instance);

static inline uint16_t read(void *instance, uint8_t *bytes);

static inline uint16_t write(void *instance, uint8_t *bytes, uint16_t size);

static inline void
transact(void *instance, uint8_t *r, uint8_t *w, uint16_t n);

static spi_interface_t interface = {
    .open = open,
    .close = close,
    .read = read,
    .write = write,
    .transact = transact,
};

SPI
stm32_spi_create() {
    self.base.vtable = &interface;
    spi_init();
    return &self.base;
}

static inline void
open(void *instance) {
    LL_SPI_Enable(instance);
    while (!LL_SPI_IsEnabled(instance));
}

static inline void
close(void *instance) {
    LL_SPI_Disable(instance);
    while (LL_SPI_IsEnabled(instance));
}

static inline uint16_t
read(void *instance, uint8_t *bytes) {
    bytes[0] = LL_SPI_ReceiveData8(instance);
    return 1;
}

static inline uint16_t
write(void *instance, uint8_t *bytes, uint16_t size) {
    for (uint8_t i = 0; i < size; i++) {
        LL_SPI_TransmitData8(instance, bytes[i]);
    }
    return size;
}

static inline void
transact(void *instance, uint8_t *r, uint8_t *w, uint16_t n) {
    while (LL_SPI_IsActiveFlag_RXNE(SPI1)) {
        LL_SPI_ReceiveData8(SPI1);
    }
    for (uint8_t i = 0; i < n; i++) {
        LL_SPI_TransmitData8(instance, w[i]);
        while (!LL_SPI_IsActiveFlag_RXNE(SPI1)) {
        }
        r[i] = LL_SPI_ReceiveData8(SPI1);
    }

}

static inline void
spi_init() {
    LL_SPI_InitTypeDef init = {0};

#if STM32_ENABLE_SPI1
    init.TransferDirection = LL_SPI_FULL_DUPLEX;
    init.Mode = LL_SPI_MODE_MASTER;
    init.DataWidth = LL_SPI_DATAWIDTH_8BIT;
    init.ClockPolarity = LL_SPI_POLARITY_LOW;
    init.ClockPhase = LL_SPI_PHASE_1EDGE;
    init.NSS = LL_SPI_NSS_SOFT;
    init.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV8;
    init.BitOrder = LL_SPI_MSB_FIRST;
    init.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
    init.CRCPoly = 7;
    LL_SPI_Init(SPI1, &init);
    LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);
    LL_SPI_DisableNSSPulseMgt(SPI1);

#endif

#if STM32_ENABLE_SPI2
    init.TransferDirection = LL_SPI_FULL_DUPLEX;
    init.Mode              = LL_SPI_MODE_SLAVE;
    init.DataWidth         = LL_SPI_DATAWIDTH_8BIT;
    init.ClockPolarity     = LL_SPI_POLARITY_LOW;
    init.ClockPhase        = LL_SPI_PHASE_1EDGE;
    init.NSS               = LL_SPI_NSS_SOFT;
    init.BitOrder          = LL_SPI_MSB_FIRST;
    init.CRCCalculation    = LL_SPI_CRCCALCULATION_DISABLE;
    init.CRCPoly           = 7;
    LL_SPI_Init(SPI2, &init);
    LL_SPI_SetStandard(SPI2, LL_SPI_PROTOCOL_MOTOROLA);
    LL_SPI_DisableNSSPulseMgt(SPI2);

#endif
}

/** @brief SPI1 interrupt handler */

void
SPI1_IRQHandler() {
}
