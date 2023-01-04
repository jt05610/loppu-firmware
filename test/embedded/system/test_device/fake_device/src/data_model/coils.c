/**
  ******************************************************************************
  * @file   coils.c
  * @author jtaylor
  * @date   03 Jan 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* start includes code */

#include "fake_device.h"
#include "coils.h"

/* end includes code */

/* start macros code */

#define N_COILS 2

/* end macros code */

/* start struct code */


static struct {
   Device base;

} self = {0};

/* end struct code */

static inline void read_on_off(sized_array_t * dest);
static inline void write_on_off(uint16_t value);
static inline void read_flash(sized_array_t * dest);
static inline void write_flash(uint16_t value);

static pt_read_t read_handlers[N_COILS] = {
    read_on_off,
    read_flash,
};

static pt_write_t write_handlers[N_COILS] = {
    write_on_off,
    write_flash,
};

static primary_table_interface_t interface = {
    .read=read_handlers,
    .write=write_handlers,
};

void
coils_create(PrimaryTable base, Device device)
{
    base->vtable = &interface;
    self.base = device;

    /* start create code */

    /* end create code */
}

/**
 * @brief reads on_off
 * @param dest Array to store results into.
 **/
static inline void
read_on_off(sized_array_t * dest)
{
    /* start read_on_off code */
    dest->size = 1;
    dest->bytes[0] = gpio_read_pin(self.base->hal->gpio, GPIO_PORT_A, 0);
    /* end read_on_off code */
}

/**
 * @brief writes on_off
 * @param value value to write to on_off.
 **/
static inline void
write_on_off(uint16_t value)
{
    /* start write_on_off code */
    if (value)
        gpio_set_pin(self.base->hal->gpio, GPIO_PORT_A, 0x01 << 0x01);
    else
        gpio_reset_pin(self.base->hal->gpio, GPIO_PORT_A, 0x01 << 0x01);
    /* end write_on_off code */
}

/**
 * @brief reads flash
 * @param dest Array to store results into.
 **/
static inline void
read_flash(sized_array_t * dest)
{
    /* start read_flash code */
    
    /* end read_flash code */
}

/**
 * @brief writes flash
 * @param value value to write to flash.
 **/
static inline void
write_flash(uint16_t value)
{
    /* start write_flash code */
    
    /* end write_flash code */
}

