#include <sys/cdefs.h>
/**
  ******************************************************************************
  * @file   needle_positioner.c
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

#include "needle_positioner.h"

#include "config.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32_timer.h"
#include "stm32g0xx_ll_exti.h"
#include "stepper/a4988_stepper.h"

static inline void
config_gpio(gpio_t *gpio)
{
    stm32_gpio_create(gpio);
    // output pins
    pin_init_t pin_init = {
            .type = NormalPin,
            .port = GPIO_PORT_A,
            .mode = LL_GPIO_MODE_OUTPUT,
            .trigger = LL_EXTI_TRIGGER_NONE
    };
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

    pin_init.pin_mask = DIR_PIN | ENABLE_PIN;
    stm32_gpio_init_pin(&pin_init);

    pin_init.type = InterruptPin;
    pin_init.mode = LL_GPIO_MODE_INPUT;
    pin_init.trigger = LL_EXTI_TRIGGER_RISING_FALLING;
    pin_init.pin_mask = BACKWARD_PIN;

    stm32_gpio_init_pin(&pin_init);

    pin_init.pin_mask = FORWARD_PIN;

    stm32_gpio_init_pin(&pin_init);
    stm32_gpio_clear_interrupt_flags(EXTI_0_1_BIT_MASK);

}

static inline void
config_time(timer_t *timer)
{
    stm32_timer_init_t init;
    init.timer = TIM16;
    init.type  = GeneralTimer;

    GEN_TIM(&init).update_freq  = UPDATE_FREQUENCY * 100;
    GEN_TIM(&init).update_delay = 100 / 2;
    GEN_TIM(&init).interrupt    = TIM16_IRQn;
    GEN_TIM(&init).clock_division    = LL_TIM_CLOCKDIVISION_DIV1;

    stm32_timer_create(timer, &init);
}

static inline void
config_pwm(pwm_t *pwm)
{
    timer_param_t params = {
            .period = 100,
            .pulse = 100,
            .prescaler = 1e6
    };


    stm32_pwm_create(pwm, TIM2, &params, STEP_PORT, STEP_PIN);

}
static inline void
config_axis_a4988(needle_positioner_t * positioner)
{
    positioner->stepper_init.step_pin = STEP_PIN;
    positioner->stepper_init.dir_pin = DIR_PIN;
    positioner->stepper_init.enable_pin = ENABLE_PIN;
    positioner->stepper_init.step_port = GPIO_PORT_A;
    positioner->stepper_init.dir_port = GPIO_PORT_A;
    positioner->stepper_init.enable_port = GPIO_PORT_A;
    positioner->stepper_init.base = &positioner->stepper;
    positioner->stepper_init.gpio = &positioner->gpio;
    a4988_stepper_create(&positioner->stepper_init);
    positioner->controller.stepper = &positioner->stepper;
    stepper_controller_create(&positioner->controller, UPDATE_FREQUENCY, &positioner->time);
    linear_axis_create(&positioner->axis, &positioner->controller, STEPS_PER_MM);
    linear_axis_set_velocity(&positioner->axis, DEFAULT_VELOCITY);
}

static inline void
config_axis_tmc22209(needle_positioner_t * positioner)
{
}

void
needle_positioner_create(needle_positioner_t * positioner)
{
    positioner->increment      = DEFAULT_INCREMENT;
    config_time(&positioner->time);
    config_pwm(&positioner->pwm);
    config_gpio(&positioner->gpio);
    buttons_create(&positioner->buttons, EXTI_0_1_BIT_MASK, 2);
    config_axis_a4988(positioner);
    linear_axis_enable(&positioner->axis);
    positioner->velocity = DEFAULT_VELOCITY;
}

void needle_positioner_set_increment(needle_positioner_t * positioner, double increment)
{
    positioner->increment = increment;
}

void needle_positioner_set_velocity(needle_positioner_t * positioner, double velocity)
{
    positioner->velocity = velocity;
}

static inline void
handle_idle(needle_positioner_t * positioner)
{

}

static inline void
handle_forward_press(needle_positioner_t * self)
{
    linear_axis_set_velocity(&self->axis, self->velocity);
    linear_axis_go_to(&self->axis, linear_axis_current_position(&self->axis) + self->increment);
}

static inline void
handle_backward_press(needle_positioner_t * self)
{
    linear_axis_set_velocity(&self->axis, -self->velocity);
    linear_axis_go_to(&self->axis, linear_axis_current_position(&self->axis) - self->increment);
}

static inline void
handle_both_press(needle_positioner_t * self)
{

}

typedef void (*position_handler_t)(needle_positioner_t * self);

static position_handler_t handlers[4] = {
        handle_idle,
        handle_forward_press,
        handle_backward_press,
        handle_both_press
};

void needle_positioner_update(needle_positioner_t * positioner)
{
    if (positioner->buttons.state > 0) {
        handlers[positioner->buttons.state](positioner);
    } else {
    }
    linear_axis_update(&positioner->axis);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
_Noreturn void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

