/**
  ******************************************************************************
  * @file   needle_positioner.h
  * @author Jonathan Taylor
  * @date   11/16/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_NEEDLE_POSITIONER_H
#define INJECTOR_NEEDLE_POSITIONER_H

#include "stm32_gpio.h"
#include "stepper/linear_axis.h"
#include "stepper/a4988_stepper.h"
#include "buttons/buttons.h"
#include "timer/timer.h"
#include "timer/pwm.h"
#include "serial/serial.h"
#include "data_model/data_model.h"
#include "data_model/api.h"

typedef struct needle_positioner_t
{
    api_t                api;
    gpio_t               gpio;
    stepper_t            stepper;
    stepper_controller_t controller;
    linear_axis_t        axis;
    a4988_init_t         stepper_init;
    buttons_t            buttons;
    timer_t              time;
    pwm_t                pwm;
    serial_t             serial;
    uint8_t             rx_buffer[RX_BUFFER_SIZE];
    data_model_t         data_model;
    double               increment;
    double               velocity;
} needle_positioner_t;

void needle_positioner_create(needle_positioner_t * positioner);

void needle_positioner_set_increment(
        needle_positioner_t * positioner, double increment);

void needle_positioner_move(needle_positioner_t * positioner, dir_t dir);

void needle_positioner_update(needle_positioner_t * positioner);

#endif //INJECTOR_NEEDLE_POSITIONER_H
