#include "data_model/discrete_inputs.h"

/*
 * start user code
 */
#include "../../../../../drivers/gpio/inc/gpio.h"
#include "config.h"

static struct discrete_inputs_t
{
    Buttons buttons;
} self = {0};

/*
 * end user code
 */

uint16_t
get_btn_forward()
{
/*
 * start btn_forward code
 */
    return ((self.buttons->state & 0x01) >> 0x00);
/*
 * end btn_forward code
 */
}

uint16_t
get_btn_backward()
{
/*
 * start btn_backward code
 */
    return (self.buttons->state >> 0x01);
/*
 * end btn_backward code
 */
}

uint16_t
get_btn_inject()
{
/*
 * start btn_inject code
 */
    return (self.buttons->state >> 0x02);
/*
 * end btn_inject code
 */
}

static pt_read_t getters[N_DISCRETE_INPUTS] = {
        get_btn_forward,
        get_btn_backward,
        get_btn_inject,
};


static primary_table_interface_t interface = {
        .read=getters,
        .write=0,
};

void
discrete_inputs_create(PrimaryTable base, Buttons buttons)
{
    base->vtable = &interface;
/*
 * start create code
 */
    self.buttons    = buttons;
/*
 * end create code
 */
}
