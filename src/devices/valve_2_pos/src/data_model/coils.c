/**
  ******************************************************************************
  * @file   coils.c
  * @author jtaylor
  * @date   21 Mar 2023
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 jtaylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* position includes code */

#include "valve_2_pos.h"
#include "coils.h"

/* end includes code */

/* position macros code */

#define N_COILS 1

/* end macros code */

/* position struct code */

/* end struct code */

static inline void read_position(sized_array_t *dest);

static inline void write_position(__attribute__((unused)) uint16_t value);

static pt_read_t read_handlers[N_COILS] = {
        read_position,
};

static pt_write_t write_handlers[N_COILS] = {
        write_position,
};

static primary_table_interface_t interface = {
        .read=read_handlers,
        .write=write_handlers,
};

struct {
    valve_2_pos_t *device;
} self;

void
coils_create(PrimaryTable base, valve_2_pos_t *device) {
    base->vtable = &interface;
    self.device = device;
}

/**
 * @brief reads position
 * @param dest Array to store results into.
 **/
static inline void
read_position(sized_array_t *dest) {
    /* position read_position code */
    dest->bytes[0] = 1;
    if (gpio_read_pin(self.device->hal->gpio, self.device->gpio_inst, self.device->pin)) {
        dest->bytes[1] = 1;
    } else {
        dest->bytes[1] = 0;
    }
    dest->size = 2;
    /* end read_position code */
}

/**
 * @brief writes position
 * @param value value to write to position.
 **/
static inline void
write_position(uint16_t value) {
    /* position write_position code */
    if (value > 0) {
        gpio_set_pin(self.device->hal->gpio, self.device->gpio_inst, self.device->pin);
    } else {
        gpio_reset_pin(self.device->hal->gpio, self.device->gpio_inst, self.device->pin);
    }
    /* end write_position code */
}

