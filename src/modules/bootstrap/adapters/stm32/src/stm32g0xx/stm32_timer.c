/**
  ******************************************************************************
  * @file   stm32_timer.c
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
#include "rcc_config.h"
#include "timer_config.h"
#include "timer_adv_config.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32_interrupts.h"
#include "stdatomic.h"

#define MAX_CALLBACKS 5

#define TIM1_INDEX 0
#define TIM2_INDEX 1
#define TIM3_INDEX 2
#define TIM17_INDEX 3

#define N_TIMERS 4

typedef void (*callback)(void);

typedef struct tim_inst_t {
    TIM_TypeDef *timer;
    callback update_cb[MAX_CALLBACKS];
    callback cc_cb[MAX_CALLBACKS];
    uint8_t n_update_cb;
    uint8_t n_cc_cb;
} tim_inst_t;

static struct {
    timer_base_t base;
    tim_inst_t timers[N_TIMERS];
    volatile uint32_t micros;
} self = {0};

static inline void start(void *timer_instance, uint32_t freq);

static inline void stop(void *timer_instance);

static inline uint32_t get_tick(void *timer_instance);

static inline void start_us_timer(void *timer_instance);

static inline void stop_us_timer(void *timer_instance);

static inline void delay(uint32_t millis);

static inline void delay_micros(uint32_t micros);

static inline uint32_t micros();

static inline uint32_t millis();

void input_cap_irq(
    void *tim_inst, uint32_t freq, uint16_t timeout_ticks, void (*cb)());

static inline void set_pwm_freq(void *timer_instance, uint32_t freq_Hz);

static inline void set_timeout(void *timer_instance, uint32_t timeout);

static inline void set_pwm_period(void *timer_instance, uint32_t period);

static inline void
set_pwm_duty_cycle(void *timer_instance, uint16_t duty_cycle);

static inline void set_pwm_callback(PeriodicCallback cb, void *data);

static inline void
start_pwm(void *instance, uint32_t freq, uint16_t duty_cycle);

static inline void stop_pwm(void *instance);

static inline void reg_update_cb(void *tim_inst, void (*cb)(void));

static inline void remove_update_cb(void *tim_inst);

static inline void reset(void *instance);

static timer_interface_t interface = {
    .start = start,
    .stop = stop,
    .get_tick = get_tick,
    .start_us_timer = start_us_timer,
    .stop_us_timer = stop_us_timer,
    .delay = delay,
    .delay_micros = delay_micros,
    .reg_update_callback = reg_update_cb,
    .reg_pwm_callback = 0,
    .set_timeout = set_timeout,
    .micros = micros,
    .millis = millis,
    .set_pwm_freq = set_pwm_freq,
    .set_pwm_period = set_pwm_period,
    .set_pwm_duty_cycle = set_pwm_duty_cycle,
    .set_pwm_callback = set_pwm_callback,
    .start_pwm = start_pwm,
    .reset = reset,
    .stop_pwm = stop_pwm
};

#define __GET(inst, param) STM32_TIM##inst##_##param

#define INIT_GEN_TIM(inst, p)                                       \
p.Prescaler     = __GET(inst, PRESCALER);                           \
p.CounterMode   = __GET(inst, COUNTER_MODE);                        \
p.Autoreload    = __GET(inst, AUTORELOAD);                          \
p.ClockDivision = __GET(inst, CLOCK_DIV);                           \
LL_TIM_Init(TIM##inst, &p);                                         \
__GET(inst, ENABLE_PRELOAD) ? LL_TIM_EnableARRPreload(TIM##inst)    \
                            : LL_TIM_DisableARRPreload(TIM##inst);  \
LL_TIM_SetClockSource(TIM##inst, __GET(inst, CLOCK_SOURCE))


static inline void
gen_tim_init() {
    LL_TIM_InitTypeDef init;

#if STM32_ENABLE_TIM1
    INIT_GEN_TIM(1, init);
#endif

#if STM32_ENABLE_TIM2
    INIT_GEN_TIM(2, init);

#endif

#if STM32_ENABLE_TIM3
    INIT_GEN_TIM(3, init);

#endif

#if STM32_ENABLE_TIM14
    INIT_GEN_TIM(14, init);
#endif

#if STM32_ENABLE_TIM16
    INIT_GEN_TIM(16, init);
#endif

#if STM32_ENABLE_TIM17
    INIT_GEN_TIM(17, init);

#endif
}

Timer
stm32_timer_create() {
    self.base.vtable = &interface;
    self.timers[TIM1_INDEX] = (tim_inst_t){
        .timer = TIM1,
        .n_update_cb = 0
    };
    self.timers[TIM2_INDEX] = (tim_inst_t){
        .timer = TIM2,
        .n_update_cb = 0
    };
    self.timers[TIM3_INDEX] = (tim_inst_t){
        .timer = TIM3,
        .n_update_cb = 0
    };

    self.timers[TIM17_INDEX] = (tim_inst_t){
        .timer = TIM17,
        .n_update_cb = 0
    };
    return &self.base;
}

static inline void
set_timeout(void *timer_instance, uint32_t timeout) {
    LL_TIM_SetAutoReload(timer_instance, timeout);
}

void
set_freq(void *t, uint32_t freq) {
    if (freq > 0) {
        LL_TIM_SetPrescaler(
            t,
            __LL_TIM_CALC_PSC(STM32_SYS_TICK, freq)
        );
    }
}

static inline void
start(void *timer_instance, uint32_t freq) {
    const uint32_t psc = __LL_TIM_CALC_PSC(STM32_SYS_TICK, freq);
    if (freq > 0) {
        LL_TIM_SetPrescaler(
            (TIM_TypeDef *) timer_instance,
            psc

        );
    }

    LL_TIM_EnableCounter((TIM_TypeDef *) timer_instance);
    while (!LL_TIM_IsEnabledCounter((TIM_TypeDef *) timer_instance));
}

static inline void
stop(void *timer_instance) {
    LL_TIM_DisableCounter((TIM_TypeDef *) timer_instance);
    while (LL_TIM_IsEnabledCounter((TIM_TypeDef *) timer_instance));
}

static inline uint32_t
get_tick(void *timer_instance) {
    return LL_TIM_GetCounter((TIM_TypeDef *) timer_instance);
}

void increment() {
    self.micros++;
}

static inline void
start_us_timer(void *timer_instance) {
    self.micros = 0;
    reg_update_cb(timer_instance, &increment);
    set_pwm_period(timer_instance, STM32_SYS_TICK / 1000000);
    start(timer_instance, STM32_SYS_TICK);
}

static inline void
stop_us_timer(void *timer_instance) {
    remove_update_cb(timer_instance);
}

static inline void
delay(uint32_t millis) {
    delay_micros(millis * 1000);
}

static inline void
reset(void *instance) {
    LL_TIM_DisableCounter(instance);
    LL_TIM_SetCounter(instance, 0);
    LL_TIM_EnableCounter(instance);
}

static inline void
delay_micros(uint32_t micros) {
    const uint32_t start = self.micros;
    while (self.micros - start < micros) {
    }
}

static inline uint32_t
micros() {
    return self.micros;
}

static inline uint32_t
millis() {
    return 1000 * self.micros;
}

static inline void
set_pwm_freq(void *timer_instance, uint32_t freq_Hz) {
    LL_TIM_SetPrescaler(
        (TIM_TypeDef *) timer_instance,
        __LL_TIM_CALC_PSC(STM32_SYS_TICK, freq_Hz)
    );
}

static inline void
set_pwm_period(void *timer_instance, uint32_t period) {
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
set_pwm_duty_cycle(void *timer_instance, uint16_t duty_cycle) {
    uint32_t val;
    val = duty_cycle / 100000;
    LL_TIM_OC_SetCompareCH1(
        (TIM_TypeDef *) timer_instance,
        val * LL_TIM_GetAutoReload((TIM_TypeDef *) timer_instance));
}

static inline void
set_pwm_callback(PeriodicCallback cb, void *data) {
}

static inline void
start_pwm(void *instance, uint32_t freq, uint16_t duty_cycle) {
}

static inline void
stop_pwm(void *instance) {
}

static inline void
reg_update_cb(void *tim_inst, void (*cb)(void)) {
    for (uint8_t i = 0; i < N_TIMERS; i++) {
        if (self.timers[i].timer == tim_inst) {
            tim_inst_t *tim = &self.timers[i];
            if (tim->n_update_cb >= MAX_CALLBACKS) {
                return;
            }
            tim->update_cb[tim->n_update_cb++] = cb;
            LL_TIM_EnableIT_UPDATE(tim_inst);
            return;
        }
    }
}

static inline void
remove_update_cb(void *tim_inst) {
    for (uint8_t i = 0; i < N_TIMERS; i++) {
        if (self.timers[i].timer == tim_inst) {
            tim_inst_t *tim = &self.timers[i];
            if (tim->n_update_cb >= MAX_CALLBACKS) {
                return;
            }
            tim->update_cb[tim->n_update_cb++] = 0;
            LL_TIM_DisableIT_UPDATE((TIM_TypeDef *) tim_inst);
            return;
        }
    }
}

void input_cap_irq(
    void *tim_inst, uint32_t freq, uint16_t timeout_ticks, void (*cb)()) {
    if (freq > 0) {
        LL_TIM_SetPrescaler(
            (TIM_TypeDef *) tim_inst,
            __LL_TIM_CALC_PSC(STM32_SYS_TICK, freq)
        );
    }

    LL_TIM_OC_InitTypeDef tim_oc = {
        .OCMode = LL_TIM_OCMODE_RETRIG_OPM1,
        .OCState = LL_TIM_OCSTATE_DISABLE,
        .OCNState = LL_TIM_OCSTATE_DISABLE,
        .CompareValue = timeout_ticks,
        .OCPolarity = LL_TIM_OCPOLARITY_HIGH,
    };
    LL_TIM_OC_Init(tim_inst, LL_TIM_CHANNEL_CH2, &tim_oc);
    LL_TIM_OC_DisableFast(tim_inst, LL_TIM_CHANNEL_CH2);
    LL_TIM_SetOnePulseMode(tim_inst, LL_TIM_ONEPULSEMODE_SINGLE);
    LL_TIM_SetTriggerInput(tim_inst, LL_TIM_TS_TI1F_ED);
    LL_TIM_SetSlaveMode(tim_inst, LL_TIM_SLAVEMODE_COMBINED_RESETTRIGGER);
    LL_TIM_CC_DisableChannel(tim_inst, LL_TIM_CHANNEL_CH1);
    LL_TIM_IC_SetFilter(tim_inst, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV1);
    LL_TIM_SetAutoReload(tim_inst, timeout_ticks + 10);
    LL_TIM_DisableIT_TRIG(tim_inst);
    LL_TIM_DisableDMAReq_TRIG(tim_inst);
    LL_TIM_EnableIT_CC2(tim_inst);
    LL_TIM_DisableIT_UPDATE(tim_inst);
    LL_TIM_SetTriggerOutput(tim_inst, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(tim_inst);
    LL_TIM_IC_SetActiveInput(
        tim_inst, LL_TIM_CHANNEL_CH1, LL_TIM_ACTIVEINPUT_TRC);
    LL_TIM_IC_SetPrescaler(tim_inst, LL_TIM_CHANNEL_CH1, LL_TIM_ICPSC_DIV1);
    LL_TIM_IC_SetPolarity(
        tim_inst, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
    for (uint8_t i = 0; i < N_TIMERS; i++) {
        if (self.timers[i].timer == tim_inst) {
            if (self.timers[i].n_cc_cb >= MAX_CALLBACKS) {
                return;
            }
            self.timers[i].cc_cb[self.timers[i].n_cc_cb++] = cb;
            LL_TIM_ClearFlag_UPDATE(tim_inst);
            LL_TIM_DisableIT_UPDATE(tim_inst);
            return;
        }
    }
}

void
run_update_cbs(uint8_t tim_index) {
    self.timers[tim_index].update_cb[0]();
}

void
run_cc_cbs(uint8_t tim_index) {
    self.timers[tim_index].cc_cb[0]();
}

__INTERRUPT
TIM1_BRK_UP_TRG_COM_IRQHandler() {
    if (LL_TIM_IsActiveFlag_UPDATE(TIM1)) {
        run_update_cbs(TIM1_INDEX);
        LL_TIM_ClearFlag_UPDATE(TIM1);
    }
}

/** @brief TIM2 interrupt handler */
__INTERRUPT
TIM2_IRQHandler() {
    if (LL_TIM_IsActiveFlag_UPDATE(TIM2)) {
        run_update_cbs(TIM2_INDEX);
        LL_TIM_ClearFlag_UPDATE(TIM2);
    }
}

/** @brief TIM3 interrupt handler */
__INTERRUPT
TIM3_IRQHandler() {
    if (LL_TIM_IsActiveFlag_CC2(TIM3)) {
        run_cc_cbs(TIM3_INDEX);
        LL_TIM_ClearFlag_CC2(TIM3);
    }
}

__INTERRUPT
TIM17_IRQHandler() {
    if (LL_TIM_IsActiveFlag_UPDATE(TIM17)) {
        run_update_cbs(TIM17_INDEX);
        LL_TIM_ClearFlag_UPDATE(TIM17);
    }
}
