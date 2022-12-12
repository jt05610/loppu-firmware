#include "data_model/input_registers.h"

/*
 * start get_user code
 */
static struct input_registers
{
    needle_positioner_t * positioner;
} self = {0};

/*
 * end get_user code
 */

uint16_t
get_current_position()
{
/*
 * start get_current_position code
 */
    return linear_axis_current_position(&self.positioner->axis);
/*
 * end get_current_position code
 */
}

uint16_t
get_button_state()
{
/*
 * start get_button_state code
 */
    return self.positioner->buttons.state;
/*
 * end get_button_state code
 */
}

uint16_t
get_current_velocity()
{
/*
 * start get_current_velocity code
 */
    return linear_axis_current_velocity(&self.positioner->axis);
/*
 * end get_current_velocity code
 */
}

static pt_read_t getters[N_INPUT_REGISTERS] = {
        get_current_position,
        get_button_state,
        get_current_velocity,
};


static primary_table_interface_t interface = {
        .read=getters,
        .write=0,
};

void
input_registers_create(PrimaryTable base, needle_positioner_t * positioner)
{
    base->vtable    = &interface;
/*
 * start get_create code
 */
    self.positioner = positioner;
/*
 * end get_create code
 */
}
