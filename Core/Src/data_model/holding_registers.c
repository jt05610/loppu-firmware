#include "data_model/holding_registers.h"

/*
 * start get_user code
 */
/*
 * end get_user code
 */

uint16_t
get_velocity()
{
/*
 * start get_velocity code
 */
    return 0;
/*
 * end get_velocity code
 */
}

uint16_t
get_target_position()
{
/*
 * start get_target_position code
 */
    return 0;
/*
 * end get_target_position code
 */
}

uint16_t
get_steps_per_mm()
{
/*
 * start get_steps_per_mm code
 */
    return 0;
/*
 * end get_steps_per_mm code
 */
}

uint16_t
get_nudge_increment()
{
/*
 * start get_nudge_increment code
 */
    return 0;
/*
 * end get_nudge_increment code
 */
}

uint16_t
set_velocity(uint16_t value)
{
/*
 * start set_velocity code
 */
    return 0;
/*
 * end set_velocity code
 */
}

uint16_t
set_target_position(uint16_t value)
{
/*
 * start set_target_position code
 */
    return 0;
/*
 * end set_target_position code
 */
}

uint16_t
set_steps_per_mm(uint16_t value)
{
/*
 * start set_steps_per_mm code
 */
    return 0;
/*
 * end set_steps_per_mm code
 */
}

uint16_t
set_nudge_increment(uint16_t value)
{
/*
 * start set_nudge_increment code
 */
    return 0;
/*
 * end set_nudge_increment code
 */
}
 
static pt_read_t getters[N_HOLDING_REGISTERS] = { 
    get_velocity,
    get_target_position,
    get_steps_per_mm,
    get_nudge_increment,
};

static pt_write_t setters[N_HOLDING_REGISTERS] = { 
    set_velocity,
    set_target_position,
    set_steps_per_mm,
    set_nudge_increment,
};


static primary_table_interface_t interface = {
        .read=getters,
        .write=setters,
};

void
holding_registers_create(PrimaryTable base)
{
    base->vtable = &interface;
/*
 * start get_create code
 */
/*
 * end get_create code
 */
}
