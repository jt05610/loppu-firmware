/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "main.h"
#include "stm32_clock.h"
#include "stm32_timer.h"
#include "config.h"
#include "needle_positioner.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_exti.h"

static needle_positioner_t self;
static volatile bool decision_time;
/**
  * @brief  The application entry point.
  * @retval int
  */
_Noreturn int
main(void)
{
    clock_config(INJECTOR_TICK);
    needle_positioner_create(&self);
    LL_TIM_EnableCounter(TIM16);
    self.axis.velocity = DEFAULT_VELOCITY;
    decision_time = false;
    stepper_kinematics_t target = {
            .position = 0,
            .velocity = self.axis.velocity,
            .acceleration = 0
    };
    while (1)
    {
        if(decision_time) {
            switch (self.buttons.state) {
                case 0x00:
                    linear_axis_disable(&self.axis);
                    timer_stop_pwm(&self.time);
                    self.controller.current_position = 0;
                    break;
                case 0x01:
                    linear_axis_enable(&self.axis);

                    stepper_set_dir(&self.stepper, Forward);
                    target.position += (self.increment * STEPS_PER_MM);
                    stepper_controller_set_target(&self.controller, &target);
                    timer_set_pwm_freq(&self.time, self.axis.velocity * STEPS_PER_MM);
                    if(!LL_TIM_IsEnabledCounter(TIM2)) {
                        linear_axis_enable(&self.axis);
                        timer_start_pwm(&self.time);
                    }
                    break;
                case 0x02:
                    linear_axis_enable(&self.axis);
                    stepper_set_dir(&self.stepper, Backward);
                    target.position -= (self.increment * STEPS_PER_MM);
                    timer_set_pwm_freq(&self.time, self.axis.velocity * STEPS_PER_MM);
                    if(!LL_TIM_IsEnabledCounter(TIM2)) {
                        linear_axis_enable(&self.axis);
                        timer_start_pwm(&self.time);
                    }
                case 0x03:
                    break;
            }
            decision_time = false;
        }
    }
}

__INTERRUPT
TIM16_IRQHandler(void)
{
    self.controller.updated = true;
    LL_TIM_ClearFlag_UPDATE(TIM16);
}

__INTERRUPT
TIM2_IRQHandler(void)
{
    self.controller.current_position ++;
    if (self.controller.current_position == self.controller.planned_steps) {
        decision_time = true;
    }
    LL_TIM_ClearFlag_UPDATE(TIM2);
}

__INTERRUPT
EXTI0_1_IRQHandler(void)
{
    buttons_handle(&self.buttons, stm32_gpio_read_interrupt_flags());
    stm32_gpio_clear_interrupt_flags(LL_EXTI_LINE_0 | LL_EXTI_LINE_1);
    decision_time = true;
}