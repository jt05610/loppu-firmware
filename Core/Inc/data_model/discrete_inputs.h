#ifndef TESTING_DISCRETE_INPUTS_H
#define TESTING_DISCRETE_INPUTS_H

#include "data_model/primary_table.h"
#include "buttons.h"

#define N_DISCRETE_INPUTS 3

/*
 * Auto generated code: changes will be overwritten!
 */

uint16_t get_btn_forward();


uint16_t get_btn_backward();


uint16_t get_btn_inject();

void discrete_inputs_create(PrimaryTable base, Buttons buttons);

/*
 * End auto generated code.
 */

/*
 * User code: changes will be saved.
 */

/*
 * End user code.
 */

#endif // TESTING_DISCRETE_INPUTS_H