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
#include "main.h"
#include "stm32_clock.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32_gpio.h"
#include "stm32_timer.h"
#include "stm32g0xx_ll_exti.h"
#include "buttons.h"
#include "config.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#define INJECTOR_TICK 16000000
#define LED_PIN LL_GPIO_PIN_5
#define LED_PORT GPIO_PORT_A

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef  hdma_usart1_rx;
DMA_HandleTypeDef  hdma_usart1_tx;

static struct
{
    gpio_t        gpio;
    timer_t       time;
    buttons_t     buttons;
    volatile bool updated;
}                  self;

static inline void
config_gpio(void)
{
    pin_init_t led_pin_init = {
            .type = NormalPin,
            .port = GPIO_PORT_A,
            .pin_mask = LED_PIN,
            .mode = LL_GPIO_MODE_OUTPUT,
            .trigger = 0
    };
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    stm32_gpio_create(&self.gpio);
    stm32_gpio_init_pin(&led_pin_init);
}



static inline void
config_time(void)
{
    self.updated = false;
    stm32_timer_init_t init;
    init.timer = TIM16;
    init.type  = GeneralTimer;

    GEN_TIM(&init).update_freq  = BLINKY_UPDATE_FREQ;
    GEN_TIM(&init).update_delay = BLINKY_DEFAULT_DELAY_US;
    GEN_TIM(&init).interrupt    = TIM16_IRQn;

    stm32_timer_create(&self.time, &init);
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    clock_config(INJECTOR_TICK);
    config_time();
    config_gpio();
    buttons_create(&self.buttons, EXTI_0_1_BIT_MASK, 2);
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /*Configure GPIO pin : PA0 */
    GPIO_InitStruct.Pin  = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
/*

    */
/*Configure GPIO pin : PA1 *//*

    GPIO_InitStruct.Pin  = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
*/

    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);
    stm32_gpio_clear_interrupt_flags(EXTI_0_1_BIT_MASK);
    LL_EXTI_EnableIT_0_31(EXTI_LINE_0);

    LL_TIM_EnableCounter(TIM16);
    while (1) {
        if (self.buttons.state > 0x00) {
            gpio_reset_pin(&self.gpio, LED_PORT, LED_PIN);
        } else {
            gpio_set_pin(&self.gpio, LED_PORT, LED_PIN);
        }
    }
}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA1_Channel1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    /* DMA1_Channel2_3_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);

    /*Configure GPIO pin : PA0 */
    GPIO_InitStruct.Pin  = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : PA1 */
    GPIO_InitStruct.Pin  = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PA4 PA5 */
    GPIO_InitStruct.Pin   = GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

void
TIM16_IRQHandler(void)
{
    self.updated = true;
    LL_TIM_ClearFlag_UPDATE(TIM16);
}

void
EXTI0_1_IRQHandler(void)
{
    buttons_handle(&self.buttons, stm32_gpio_read_interrupt_flags());
    stm32_gpio_clear_interrupt_flags(EXTI_0_1_BIT_MASK);
}

#pragma clang diagnostic pop