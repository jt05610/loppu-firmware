//
// Created by taylojon on 12/6/2022.
//

#ifndef INJECTOR_COILS_H
#define INJECTOR_COILS_H

#include "data_model/primary_table.h"
#include "needle_positioner.h"

#define N_COILS 4

/*
 * Auto generated code: changes will be overwritten!
 */
uint16_t get_home();

uint16_t get_go_to_target();

uint16_t get_stop();

uint16_t get_nudge();

uint16_t set_home(uint16_t value);

uint16_t set_go_to_target(uint16_t value);

uint16_t set_stop(uint16_t value);

uint16_t set_nudge(uint16_t value);

void coils_create(PrimaryTable base, needle_positioner_t * positioner);

/*
 * End auto generated code.
 */

/*
 * User code: changes will be saved.
 */

/*
 * End user code.
 */

#endif //INJECTOR_COILS_H
