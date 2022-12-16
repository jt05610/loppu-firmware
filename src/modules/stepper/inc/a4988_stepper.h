//
// Created by taylojon on 7/19/2022.
//

#ifndef DRIVERS_A4988_STEPPER_H
#define DRIVERS_A4988_STEPPER_H

#include "stepper_driver.h"
#include "../../../lib/drivers/gpio/inc/gpio.h"

#ifdef A4988
#include "a4988_config.h"
#endif
#ifndef A4988_CONFIG
#define MS1_PIN 1
#define MS2_PIN 2
#define MS3_PIN 3
#define SLEEP_PIN 1
#define RESET_PIN 1
#define MS_PORT GPIO_PORT_A
#define RESET_PORT GPIO_PORT_A
#define SLEEP_PORT GPIO_PORT_A
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
    gpio_pin_t step_pin;
    gpio_pin_t dir_pin;
    gpio_port_t step_port;
    gpio_port_t dir_port;
    gpio_pin_t enable_pin;
    gpio_port_t enable_port;
    gpio_pin_t sleep_pin;
    gpio_port_t sleep_port;
    gpio_pin_t reset_pin;
    gpio_port_t reset_port;
} a4988_init_t;

void a4988_stepper_create(a4988_init_t * params);

void a4988_sleep(Stepper base);

void a4988_wakeup(Stepper base);

void a4988_reset(Stepper base);

void a4988_set(Stepper base);

#endif //DRIVERS_A4988_STEPPER_H
