/**
  ******************************************************************************
  * @file   stm32_timer.h
  * @author Jonathan Taylor
  * @date   6/30/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef STM32_IMPL_STM32_TIMER_H
#define STM32_IMPL_STM32_TIMER_H

#include "stm32g0xx_ll_tim.h"
#include "timer/timer.h"
#include "timer/pwm.h"

#define MAX_PWM_INSTANCES 2

typedef struct stm32_timer_init_t      * STM32TimerInit;
typedef struct stm32_adv_timer_init_t  * AdvancedTimerInit;
typedef struct stm32_gen_timer_init_t  * GeneralTimerInit;
typedef union stm32_timer_init_union_t * STM32TimerInitUnion;

typedef enum timer_type_t
{
    GeneralTimer,
    AdvancedTimer

} timer_type_t;

typedef struct stm32_adv_timer_init_t
{
    GeneralTimerInit gen;
} stm32_adv_timer_init_t;

typedef struct stm32_gen_timer_init_t
{
    uint32_t  update_freq;
    uint32_t  update_delay;
    uint32_t  counter_mode;
    uint32_t  clock_division;
    IRQn_Type interrupt;
    uint8_t   repetition_counter;
    uint32_t  clock_source;
    bool auto_reload_preload;
} stm32_gen_timer_init_t;

typedef union stm32_timer_init_union_t
{
    stm32_adv_timer_init_t adv;
    stm32_gen_timer_init_t gen;
} stm32_timer_init_union_t;

typedef struct stm32_timer_init_t
{
    TIM_TypeDef * timer;
    timer_type_t             type;
    stm32_timer_init_union_t params;

} stm32_timer_init_t;

#define ADV_TIM(tim) ((tim)->params.adv)
#define GEN_TIM(tim) ((tim)->params.gen)

void stm32_timer_create(Timer base, STM32TimerInit params);

void stm32_pwm_create(
        PWM base,
        TIM_TypeDef * timer,
        timer_param_t * params,
        gpio_port_t port,
        gpio_pin_t pin
);

void stm32_set_event_delay(uint16_t delay);

#endif //STM32_IMPL_STM32_TIMER_H
