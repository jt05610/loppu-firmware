//
// Created by taylojon on 7/19/2022.
//

#ifndef DRIVERS_A4988_STEPPER_H
#define DRIVERS_A4988_STEPPER_H

#include "stepper/stepper.h"
#include "gpio/gpio.h"

#ifdef A4988
#include "a4988_config.h"
#endif
#ifndef A4988_CONFIG
#define MS1_PIN 1
#define MS2_PIN 2
#define MS3_PIN 3
#define DIR_PIN 1
#define STEP_PIN 1
#define SLEEP_PIN 1
#define RESET_PIN 1
#define ENABLE_PIN 1
#define MS_PORT GPIO_PORT_A
#define RESET_PORT GPIO_PORT_A
#define SLEEP_PORT GPIO_PORT_A
#define ENABLE_PORT GPIO_PORT_A
#define DIR_PORT GPIO_PORT_A
#define STEP_PORT GPIO_PORT_A
#endif

#ifndef SYS_TICK
#define SYS_TICK 16000000
#endif

#define A4988_MAX_SPEED 500     /* steps / s */

#define UPDATE_FREQ 1000000 /* Hz */

#define RESET_PINS_FULL (MS1_PIN | MS2_PIN | MS3_PIN)
#define RESET_PINS_HALF (MS2_PIN | MS3_PIN)
#define RESET_PINS_QUARTER (MS1_PIN | MS3_PIN)
#define RESET_PINS_EIGHTH (MS3_PIN)

#define SET_PINS_HALF (MS1_PIN)
#define SET_PINS_QUARTER (MS2_PIN)
#define SET_PINS_EIGHTH (MS1_PIN | MS2_PIN)
#define SET_PINS_SIXTEENTH (MS1_PIN | MS2_PIN | MS3_PIN)

typedef struct a4988_init_t
{
    Stepper  base;
    GPIO     gpio;
    Timer    time;
    PWM      pwm;
    uint32_t sys_tick;
} a4988_init_t;

uint32_t get_position();

void a4988_stepper_create(a4988_init_t * params);

void a4988_set_microstep(microstep_t microstep);

void a4988_reset();

void a4988_set();

void a4988_enable();

void a4988_disable();

void a4988_sleep();

void a4988_wakeup();

void a4988_us_interrupt();

#endif //DRIVERS_A4988_STEPPER_H
