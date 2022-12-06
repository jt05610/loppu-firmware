#include "data_model/coils.h"
#include "config.h"
#include "stm32g0xx_ll_tim.h"

/*
 * start get_user code
 */
static struct coils_t
{
    needle_positioner_t * positioner;
} self = {0};

/*
 * end get_user code
 */

uint16_t
get_home()
{
/*
 * start get_home code
 */
    return get_go_to_target();
/*
 * end get_home code
 */
}

/**
 * Returns if needle is currently moving
 * @return 1 if needle is moving else 0
 */
uint16_t
get_go_to_target()
{
/*
 * start get_go_to_target code
 */
    return self.positioner->controller.current_position !=
           self.positioner->controller.planned_steps;
/*
 * end get_go_to_target code
 */
}

/**
 * Returns if needle is stopped
 * @return
 */
uint16_t
get_stop()
{
/*
 * start get_stop code
 */
    return !get_go_to_target();
/*
 * end get_stop code
 */
}

/**
 * Returns if needle is moving
 * @return
 */
uint16_t
get_nudge()
{
/*
 * start get_nudge code
 */
    return get_go_to_target();
/*
 * end get_nudge code
 */
}

/**
 * Starts homing procedure if 1 is written otherwise stops it
 * @param value: 1 if start homing else 0
 * @return value if successful, else 0xFF
 */
uint16_t
set_home(uint16_t value)
{
/*
 * start set_home code
 */
    if(value) {
        stepper_set_dir(&self.positioner->stepper, Backward);
        self.positioner->controller.current_position = 0xFFFFFFFF;
        self.positioner->target.position = 0;
    } else {
        return set_stop(0);
    }

    return set_go_to_target(1);
/*
 * end set_home code
 */
}

/**
 * Starts moving to set target if 1 is written otherwise stops it
 * @param value: 1 if start homing else 0
 * @return value if successful, else 0xFF
 */
uint16_t
set_go_to_target(uint16_t value)
{
/*
 * start set_go_to_target code
 */
    if(value) {
        stepper_controller_set_target(
                &self.positioner->controller, &self.positioner->target);
        if (!LL_TIM_IsEnabledCounter(TIM2))
        {
            linear_axis_enable(&self.positioner->axis);
            timer_start_pwm(&self.positioner->time);
        }
    } else {
        return set_stop(0);
    }
    return value;
/*
 * end set_go_to_target code
 */
}

/**
 * Stops no matter what is written
 * @param value: doesnt matter, will try to stop asap
 * @return value if successful, else 0xFF
 */
uint16_t
set_stop(uint16_t value)
{
/*
 * start set_stop code
 */
    self.positioner->target.position = self.positioner->controller.current_position;
    self.positioner->target.velocity = 0;
    return set_go_to_target(1);
/*
 * end set_stop code
 */
}

/**
 * Starts nudging if 1 is written otherwise stops it
 * @param value: 1 if start homing else 0
 * @return value if successful, else 0xFF
 */
uint16_t
set_nudge(uint16_t value)
{
/*
 * start set_nudge code
 */
    if (value)
    {
        self.positioner->target.position += (self.positioner->increment *
                                             STEPS_PER_MM);
    } else
    {
        return set_stop(0);
    }
    return set_go_to_target(1);
/*
 * end set_nudge code
 */
}

static pt_read_t getters[N_COILS] = {
        get_home,
        get_go_to_target,
        get_stop,
        get_nudge,
};

static pt_write_t setters[N_COILS] = {
        set_home,
        set_go_to_target,
        set_stop,
        set_nudge,
};

static primary_table_interface_t interface = {
        .read=getters,
        .write=setters,
};

void
coils_create(PrimaryTable base, needle_positioner_t * positioner)
{
    base->vtable = &interface;
/*
 * start get_create code
 */
/*
 * end get_create code
 */
}
