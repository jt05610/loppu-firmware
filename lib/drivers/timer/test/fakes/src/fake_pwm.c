//
// Created by Jonathan Taylor on 4/28/22.
//

#include "stdint.h"
#include "fake_pwm.h"

typedef struct fake_pwm_t
{
    PWM      base;
    uint32_t counter;
} fake_pwm_t;

static struct fake_pwm_container
{
    fake_pwm_t instances[MAX_FAKE_PWM_INSTANCES];
    uint8_t    n_instances;
    pwm_callback_t * callbacks[MAX_CALLBACKS];
    uint8_t           n_callbacks;
    pwm_timer_state_t last_state;
} self = {0};

#define INST(base) self.instances[(base)->instance]

static pwm_timer_state_t read_state(void);

static void register_callback(pwm_callback_t * callback);

static void run_callbacks(void);

static void set_period(PWM pwm, uint32_t period);

static void set_pulse(PWM pwm, uint32_t pulse);

static void set_prescaler(PWM pwm, uint32_t prescaler);

uint16_t
fake_pwm_read_counter(PWM timer)
{
    return INST(timer).counter;
}

void
fake_pwm_set_counter(PWM timer, uint16_t count)
{
    INST(timer).counter = count;
}

void
fake_pwm_increment_counter(PWM timer)
{
    INST(timer).counter++;
}

static pwm_interface_t client_dl_interface = {
        .set_period=set_period,
        .set_pulse=set_pulse,
        .set_prescaler=set_prescaler,
        .read_state=read_state,
        .register_callback=register_callback,
        .run_callbacks=run_callbacks
};

void
fake_pwm_create(pwm_t * timer, timer_param_t * params)
{
    if (self.n_instances < MAX_FAKE_PWM_INSTANCES)
    {
        timer->vtable   = &client_dl_interface;
        timer->instance = self.n_instances++;
        timer->params   = params;
        INST(timer).counter = 0;
        INST(timer).base    = timer;
    }
}

uint8_t
fake_pwm_get_n_instances()
{
    return self.n_instances;
}

void
fake_pwm_reset()
{
    self.n_instances = 0;
    self.n_callbacks = 0;
}

static inline uint8_t
state(pwm_instance_t instance)
{
    return self.instances[instance].counter %
           self.instances[instance].base->params->period
           < self.instances[instance].base->params->pulse;
}

pwm_single_timer_state_t
fake_pwm_timer_state(PWM timer)
{
    return state(timer->instance);
}

uint8_t
fake_pwm_n_callbacks()
{
    return self.n_callbacks;
}

pwm_callback_t *
fake_pwm_get_callback(uint8_t n)
{
    pwm_callback_t * result = 0;
    if (n < self.n_callbacks)
        result = self.callbacks[n];
    return result;
}

static pwm_timer_state_t
read_state(void)
{
    pwm_timer_state_t ret = 0;
    for (uint8_t      i   = 0; i < self.n_instances; i++)
        ret |= state(i) << i;

    return ret;
}

static void
register_callback(pwm_callback_t * callback)
{
    if (self.n_callbacks < MAX_CALLBACKS)
        self.callbacks[self.n_callbacks++] = callback;
}

static void
run_callbacks(void)
{
    pwm_timer_state_t state = read_state();

    for (uint8_t i = 0; i < self.n_callbacks; i++)
    {
        if (state == self.callbacks[i]->on && state != self.last_state)
        {
            self.callbacks[i]->action();
        }
    }
    self.last_state = state;
}

void
set_period(PWM pwm, uint32_t period)
{
    pwm->params->period = period;
}

void
set_pulse(PWM pwm, uint32_t pulse)
{
    if (pulse < pwm->params->period)
        pwm->params->pulse = pulse;
}

void
set_prescaler(PWM pwm, uint32_t prescaler)
{
    pwm->params->prescaler = prescaler;
}