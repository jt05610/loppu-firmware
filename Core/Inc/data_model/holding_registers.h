//
// Created by taylojon on 12/6/2022.
//

#ifndef INJECTOR_HOLDING_REGISTERS_H
#define INJECTOR_HOLDING_REGISTERS_H
#include "data_model/primary_table.h"
#include "needle_positioner.h"

#define N_HOLDING_REGISTERS 4


uint16_t get_velocity();

uint16_t get_target_position();

uint16_t get_steps_per_mm();

uint16_t get_nudge_increment();

uint16_t set_velocity(uint16_t value);

uint16_t set_target_position(uint16_t value);

uint16_t set_steps_per_mm(uint16_t value);

uint16_t set_nudge_increment(uint16_t value);

void
holding_registers_create(PrimaryTable base, needle_positioner_t * positioner);

#endif //INJECTOR_HOLDING_REGISTERS_H
