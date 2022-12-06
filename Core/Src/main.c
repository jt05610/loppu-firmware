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
#include <string.h>
#include "main.h"
#include "stm32_clock.h"
#include "stm32_timer.h"
#include "config.h"
#include "needle_positioner.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32_uart.h"
#include "data_model/api.h"
#include "modbus.h"

static needle_positioner_t self;
volatile bool              clear_to_send;
volatile bool              idle_line;
static volatile bool       decision_time;
static volatile bool       processed;

/**
  * @brief  The application entry point.
  * @retval int
  */
_Noreturn int
main(void)
{
    clock_config(INJECTOR_TICK);
    needle_positioner_create(&self);
    self.axis.velocity = DEFAULT_VELOCITY;
    decision_time               = false;
    clear_to_send               = true;
    idle_line                   = true;
    processed                   = false;
    stepper_kinematics_t target = {
            .position = 0,
            .velocity = self.axis.velocity,
            .acceleration = 0
    };
    LL_TIM_EnableCounter(TIM16);

    while (1)
    {
        if (decision_time)
        {
            switch (self.buttons.state)
            {
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
                    timer_set_pwm_freq(
                            &self.time, self.axis.velocity * STEPS_PER_MM);
                    if (!LL_TIM_IsEnabledCounter(TIM2))
                    {
                        linear_axis_enable(&self.axis);
                        timer_start_pwm(&self.time);
                    }
                    break;
                case 0x02:
                    linear_axis_enable(&self.axis);
                    stepper_set_dir(&self.stepper, Backward);
                    target.position -= (self.increment * STEPS_PER_MM);
                    timer_set_pwm_freq(
                            &self.time, self.axis.velocity * STEPS_PER_MM);
                    if (!LL_TIM_IsEnabledCounter(TIM2))
                    {
                        linear_axis_enable(&self.axis);
                        timer_start_pwm(&self.time);
                    }
                case 0x03:
                    break;
            }
            decision_time = false;
        }
        api_poll(&self.api);
    }
}

__INTERRUPT
TIM16_IRQHandler(void)
{
    if (!clear_to_send && idle_line)
    {
        clear_to_send = true;
    }
    LL_TIM_ClearFlag_UPDATE(TIM16);
}

__INTERRUPT
TIM2_IRQHandler(void)
{
    self.controller.current_position++;
    if (self.controller.current_position == self.controller.planned_steps)
    {
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

__INTERRUPT
DMA1_Channel1_IRQHandler(void)
{
    stm32_dma_transfer(DMA_BUFF_SIZE);
    LL_DMA_ClearFlag_TC1(DMA1);
    self.api.target_pos += DMA_BUFF_SIZE;
    LL_DMA_DisableChannel(RX_DMA, RX_CHANNEL);
    LL_DMA_SetDataLength(RX_DMA, RX_CHANNEL, DMA_BUFF_SIZE);
    LL_DMA_EnableChannel(RX_DMA, RX_CHANNEL);
}

__INTERRUPT
USART1_IRQHandler(void)
{
    if (LL_USART_IsActiveFlag_TC(USART1))
    {
        LL_GPIO_ResetOutputPin(DE_PORT, RE_PIN);
        LL_USART_ClearFlag_TC(USART1);
        idle_line = true;
    }
    if (LL_USART_IsActiveFlag_RXNE_RXFNE(USART1)) {
        return;
    } else if (LL_USART_IsActiveFlag_RTO(USART1))
    {
        if (DMA1_Channel1->CNDTR != DMA_BUFF_SIZE) {
            if (LL_DMA_IsActiveFlag_TC1(DMA1)) return;
            stm32_dma_transfer(DMA_BUFF_SIZE - DMA1_Channel1->CNDTR);
            stm32_serial_pos_t * pos = stm32_serial_current_pos();
            self.api.target_pos += pos->new;
        }
        LL_USART_ClearFlag_RTO(USART1);
        self.api.new_data   = true;
    }
}

uint16_t
api_read_handler(uint32_t address)
{
    return api_read(&self.api, address);
}

uint16_t
api_write_handler(uint32_t address, uint16_t value)
{
    return api_write(&self.api, address, value);
}

int
api_send_handler(
        const mbus_t context, const uint8_t * data, const uint16_t size)
{
    sized_array_t array = {.bytes=data, .size=size};
    serial_write(&self.serial, &array);

    return size;
}
