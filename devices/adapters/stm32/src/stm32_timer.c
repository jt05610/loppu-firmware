/**
  ******************************************************************************
  * @file   stm32_timer.c
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
#include "../../../../drivers/gpio/inc/gpio.h"
#include "stm32g0xx_ll_tim.h"
#include "stm32g0xx_ll_bus.h"
#include "system_stm32g0xx.h"
#include "stm32_assert.h"

#include "stm32_timer.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32_gpio.h"

#define INST(base) pwm_container.instances[(base)->instance].pwm
#define TIM_INST(base) pwm_container.instances[(base)->instance].timer

#define PWM_FREQ (uint32_t) 1e5

static struct stm32_timer_t
{
    TIM_TypeDef * timer;
} self = {0};

typedef struct stm32_pwm_t
{
    PWM pwm;
    TIM_TypeDef * timer;
} stm32_pwm_t;

static struct
{
    stm32_pwm_t instances[MAX_PWM_INSTANCES];
    uint8_t     n_instances;

} pwm_container = {0};

static inline void set_period(PWM pwm, uint32_t period);

static inline void set_pulse(PWM pwm, uint32_t pulse);

static inline void set_prescaler(PWM pwm, uint32_t prescaler);

static void delay(uint32_t millis);

static void delay_micros(uint32_t micros);

static uint32_t micros();

static uint32_t millis();

static ErrorStatus gen_tim_init(TIM_TypeDef * timer, GeneralTimerInit params);

static ErrorStatus adv_tim_init(TIM_TypeDef * timer, AdvancedTimerInit params);

static void apb_setup(const TIM_TypeDef * timer);

static void
set_pwm_freq(uint32_t freq_Hz)
{
    // TODO dont hardcode tim2
    LL_TIM_SetAutoReload(TIM2, PWM_FREQ / freq_Hz);
    LL_TIM_OC_SetCompareCH1(TIM2, PWM_FREQ / (2*freq_Hz));
}

static void
start_pwm()
{
    LL_TIM_EnableCounter(TIM2);

}

static void
stop_pwm()
{
    LL_TIM_DisableCounter(TIM2);
}

static timer_interface_t interface = {
        .delay=delay,
        .delay_micros=delay_micros,
        .micros=micros,
        .millis=millis,
        .set_pwm_freq=set_pwm_freq,
        .start_pwm=start_pwm,
        .stop_pwm=stop_pwm
};


static pwm_interface_t pwm_interface = {
        .set_period = set_period,
        .set_pulse = set_pulse,
        .set_prescaler = set_prescaler
};

void
stm32_timer_create(Timer base, STM32TimerInit params)
{
    base->vtable = &interface;
    self.timer   = params->timer;
    if (GeneralTimer == params->type)
        gen_tim_init(params->timer, &GEN_TIM(params));
    if (AdvancedTimer == params->type)
        adv_tim_init(params->timer, &ADV_TIM(params));
}

static inline void
pwm_tim_init(
        TIM_TypeDef * timer,
        gpio_port_t port,
        gpio_pin_t pin,
        timer_param_t * params
)
{

    LL_TIM_InitTypeDef    tim_init    = {0};
    LL_TIM_OC_InitTypeDef tim_oc_init = {0};

    LL_GPIO_InitTypeDef gpio_init = {0};

    /* Peripheral clock enable */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    /* USER CODE BEGIN TIM2_Init 1 */

    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);
    /* USER CODE END TIM2_Init 1 */
    tim_init.Prescaler     = __LL_TIM_CALC_PSC(SystemCoreClock, PWM_FREQ);
    tim_init.CounterMode   = LL_TIM_COUNTERMODE_UP;
    tim_init.Autoreload    = PWM_FREQ / params->period;  // unit 10µs^-1
    tim_init.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(timer, &tim_init);
    LL_TIM_DisableARRPreload(timer);
    LL_TIM_SetClockSource(timer, LL_TIM_CLOCKSOURCE_INTERNAL);
    LL_TIM_OC_EnablePreload(timer, LL_TIM_CHANNEL_CH1);
    tim_oc_init.OCMode       = LL_TIM_OCMODE_PWM1;
    tim_oc_init.OCState      = LL_TIM_OCSTATE_ENABLE;
    tim_oc_init.OCNState     = LL_TIM_OCSTATE_DISABLE;
    tim_oc_init.CompareValue = calculate_pulse(tim_init.Autoreload, 50);
    tim_oc_init.OCPolarity   = LL_TIM_OCPOLARITY_HIGH;
    LL_TIM_OC_Init(timer, LL_TIM_CHANNEL_CH1, &tim_oc_init);
    LL_TIM_OC_DisableFast(timer, LL_TIM_CHANNEL_CH1);
    LL_TIM_SetTriggerOutput(timer, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(timer);

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /**TIM2 GPIO Configuration
    PA1   ------> TIM2_CH2
    */
    gpio_init.Pin        = pin;
    gpio_init.Mode       = LL_GPIO_MODE_ALTERNATE;
    gpio_init.Speed      = LL_GPIO_SPEED_FREQ_LOW;
    gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_init.Pull       = LL_GPIO_PULL_NO;
    gpio_init.Alternate  = LL_GPIO_AF_2;
    LL_GPIO_Init(STM_PORT(port), &gpio_init);
}

void
stm32_pwm_create(
        PWM base,
        TIM_TypeDef * timer,
        timer_param_t * params,
        gpio_port_t port,
        gpio_pin_t pin
)
{
    if (pwm_container.n_instances < MAX_PWM_INSTANCES)
    {
        base->vtable   = &pwm_interface;
        base->instance = pwm_container.n_instances++;
        base->params   = params;
        INST(base)     = base;
        TIM_INST(base) = timer;
        pwm_tim_init(timer, port, pin, params);
        LL_TIM_EnableIT_UPDATE(TIM2);
    }
}

static void
delay(uint32_t _millis)
{
    uint32_t start = millis();
    while (millis() - start < _millis);
}

static void
delay_micros(uint32_t _micros)
{
    uint32_t start = micros();
    while (micros() - start < _micros);
}

static uint32_t
micros()
{
    return READ_REG(self.timer->CNT);
}

static uint32_t
millis()
{
    return READ_REG(self.timer->CNT) * 1000;
}

void
stm32_set_event_delay(uint16_t delay)
{
    // TODO calculate
    LL_TIM_SetAutoReload(
            self.timer,
            __LL_TIM_CALC_DELAY(
                    SystemCoreClock,
                    LL_TIM_GetPrescaler(self.timer),
                    delay
            )
    );
}

static ErrorStatus
gen_tim_init(TIM_TypeDef * timer, GeneralTimerInit params)
{
    uint32_t temp_cr1;

    assert_param(IS_TIM_INSTANCE(timer));
    apb_setup(timer);


    if (TIM1_BRK_UP_TRG_COM_IRQn <= params->interrupt
        && TIM17_IRQn >= params->interrupt)
    {
        NVIC_SetPriority(params->interrupt, 0);
        NVIC_EnableIRQ(params->interrupt);
        LL_TIM_EnableIT_UPDATE(TIM16);
    }

    assert_param(IS_LL_TIM_COUNTERMODE(params->counter_mode));
    assert_param(IS_LL_TIM_CLOCKDIVISION(params->clock_division));

    temp_cr1 = LL_TIM_ReadReg(timer, CR1);

    if (IS_TIM_COUNTER_MODE_SELECT_INSTANCE(timer))
        MODIFY_REG(
                temp_cr1, (TIM_CR1_DIR | TIM_CR1_CMS),
                params->counter_mode
        );

    if (IS_TIM_CLOCK_DIVISION_INSTANCE(timer))
        MODIFY_REG(temp_cr1, TIM_CR1_CKD, params->clock_division);

    LL_TIM_WriteReg(timer, CR1, temp_cr1);

    LL_TIM_SetPrescaler(
            timer,
            __LL_TIM_CALC_PSC(SystemCoreClock, params->update_freq)
    );

    LL_TIM_SetAutoReload(
            timer,
            __LL_TIM_CALC_DELAY(
                    SystemCoreClock,
                    LL_TIM_GetPrescaler(timer),
                    params->update_delay * 1000
            )
    );

    if (IS_TIM_REPETITION_COUNTER_INSTANCE(timer))
        LL_TIM_SetRepetitionCounter(
                timer,
                params->repetition_counter
        );

    if (!params->auto_reload_preload)
        LL_TIM_DisableARRPreload(timer);

    LL_TIM_SetClockSource(timer, params->clock_source);

    return SUCCESS;
}

static ErrorStatus
adv_tim_init(TIM_TypeDef * timer, AdvancedTimerInit params)
{
    gen_tim_init(timer, params->gen);
    return SUCCESS;
}

static void
apb_setup(const TIM_TypeDef * timer)
{
    if (TIM1 == timer)
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
    else if (TIM2 == timer)
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
    else if (TIM3 == timer)
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
    else if (TIM14 == timer)
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM14);
    else if (TIM16 == timer)
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);
    else if (TIM17 == timer)
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17);
}

static inline void
set_period(PWM pwm, uint32_t period)
{
    WRITE_REG(TIM_INST(pwm)->ARR, period);
    pwm->params->period = period;
}

static inline void
set_pulse(PWM pwm, uint32_t pulse)
{
    WRITE_REG(TIM_INST(pwm)->CCR2, pulse);
    pwm->params->pulse = pulse;
}

static inline void
set_prescaler(PWM pwm, uint32_t prescaler)
{
    WRITE_REG(TIM_INST(pwm)->PSC, prescaler);
    pwm->params->prescaler = prescaler;
}
