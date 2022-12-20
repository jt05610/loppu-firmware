/**
  ******************************************************************************
  * @file   timer.c
  * @author Jonathan Taylor
  * @date   12/13/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32_timer.h"
#include "default/rcc_config.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32_interrupts.h"

static struct
{
    timer_base_t base;
    TIM_TypeDef * micros_timer;
} self = {0};

static inline void start(void * timer_instance, uint32_t freq);

static inline void stop(void * timer_instance);

static inline uint32_t get_tick(void * timer_instance);

static inline void start_us_timer(void * timer_instance);

static inline void stop_us_timer(void * timer_instance);

static inline void delay(uint32_t millis);

static inline void delay_micros(uint32_t micros);

static inline uint32_t micros();

static inline uint32_t millis();

static inline void set_pwm_freq(void * timer_instance, uint32_t freq_Hz);

static inline void set_pwm_period(void * timer_instance, uint32_t period);

static inline void
set_pwm_duty_cycle(void * timer_instance, uint16_t duty_cycle);

static inline void set_pwm_callback(PeriodicCallback cb, void * data);

static inline void
start_pwm(void * instance, uint32_t freq, uint16_t duty_cycle);

static inline void stop_pwm(void * instance);

static timer_interface_t interface = {
        .start=start,
        .stop=stop,
        .get_tick=get_tick,
        .start_us_timer=start_us_timer,
        .stop_us_timer=stop_us_timer,
        .delay=delay,
        .delay_micros=delay_micros,
        .micros=micros,
        .millis=millis,
        .set_pwm_freq=set_pwm_freq,
        .set_pwm_period=set_pwm_period,
        .set_pwm_duty_cycle=set_pwm_duty_cycle,
        .set_pwm_callback=set_pwm_callback,
        .start_pwm=start_pwm,
        .stop_pwm=stop_pwm
};

Timer
stm32_timer_create()
{
    self.base.vtable = &interface;
    return &self.base;
}

static inline void
start(void * timer_instance, uint32_t freq)
{
    LL_TIM_SetPrescaler(
            (TIM_TypeDef *) timer_instance,
            __LL_TIM_CALC_PSC(STM32_SYS_TICK, freq)
    );
    LL_TIM_EnableCounter((TIM_TypeDef *) timer_instance);
    while (!LL_TIM_IsEnabledCounter((TIM_TypeDef *) timer_instance));
}

static inline void
stop(void * timer_instance)
{
    LL_TIM_DisableCounter((TIM_TypeDef *) timer_instance);
    while (LL_TIM_IsEnabledCounter((TIM_TypeDef *) timer_instance));
}

static inline uint32_t
get_tick(void * timer_instance)
{
    return LL_TIM_GetCounter((TIM_TypeDef *) timer_instance);
}

static inline void
start_us_timer(void * timer_instance)
{
    self.micros_timer = (TIM_TypeDef *) timer_instance;
    start(self.micros_timer, 100000);
}

static inline void
stop_us_timer(void * timer_instance)
{
    stop(self.micros_timer);
}

static inline void
delay(uint32_t millis)
{
    delay_micros(millis * 1000);
}

static inline void
delay_micros(uint32_t micros)
{
    if (LL_TIM_IsEnabledCounter(self.micros_timer)) {
        uint32_t start = get_tick(self.micros_timer);
        while (get_tick(self.micros_timer) - start < micros);
    }
}

static inline uint32_t
micros()
{
    if (LL_TIM_IsEnabledCounter(self.micros_timer)) {

        return get_tick(self.micros_timer);
    }
    return 0;
}

static inline uint32_t
millis()
{
    if (LL_TIM_IsEnabledCounter(self.micros_timer)) {

        return 1000 * get_tick(self.micros_timer);
    }
    return 0;
}

static inline void
set_pwm_freq(void * timer_instance, uint32_t freq_Hz)
{
    LL_TIM_SetPrescaler(
            (TIM_TypeDef *) timer_instance,
            __LL_TIM_CALC_PSC(STM32_SYS_TICK, freq_Hz)
    );
}

static inline void
set_pwm_period(void * timer_instance, uint32_t period)
{
    LL_TIM_SetAutoReload(
            (TIM_TypeDef *) timer_instance,
            __LL_TIM_CALC_ARR(
                    STM32_SYS_TICK,
                    LL_TIM_GetPrescaler((TIM_TypeDef *) timer_instance),
                    period
            )
    );
}

static inline void
set_pwm_duty_cycle(void * timer_instance, uint16_t duty_cycle)
{
    uint32_t val;
    val = duty_cycle / 100000;
    LL_TIM_OC_SetCompareCH1(
            (TIM_TypeDef *) timer_instance,
            val * LL_TIM_GetAutoReload((TIM_TypeDef *) timer_instance));

}


static inline void
set_pwm_callback(PeriodicCallback cb, void * data)
{

}

static inline void
start_pwm(void * instance, uint32_t freq, uint16_t duty_cycle)
{

}

static inline void
stop_pwm(void * instance)
{

}

