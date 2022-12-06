//
// Created by taylojon on 12/6/2022.
//

#ifndef INJECTOR_INPUT_REGISTERS_H
#define INJECTOR_INPUT_REGISTERS_H

#include "data_model/primary_table.h"
#include "needle_positioner.h"

#define N_INPUT_REGISTERS 3

uint16_t get_current_position();

uint16_t get_button_state();

uint16_t get_current_velocity();

void
input_registers_create(PrimaryTable base, needle_positioner_t * positioner);

#endif //INJECTOR_INPUT_REGISTERS_H
