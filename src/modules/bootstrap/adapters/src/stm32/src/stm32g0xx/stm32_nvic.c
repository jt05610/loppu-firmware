/**
  ******************************************************************************
  * @file   stm32_nvic.c
  * @author Jonathan Taylor
  * @date   12/17/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32g031xx.h"
#include "stm32_nvic.h"
#include "default/nvic_config.h"

#define NVIC_INIT(i, p) NVIC_SetPriority((i), (p)); NVIC_EnableIRQ((i))

static inline void
ungrouped_init()
{
#if STM32_ENABLE_WWDG_IRQn
    NVIC_INIT(WWDG_IRQn, STM32_WWDG_IRQn_PRIORITY)
#endif // STM32_ENABLE_WWDG_IRQn

#if STM32_ENABLE_PVD_IRQn
    NVIC_INIT(PVD_IRQn, STM32_PVD_IRQn_PRIORITY);
#endif // STM32_ENABLE_PVD_IRQn

#if STM32_ENABLE_RTC_TAMP_IRQn
    NVIC_INIT(RTC_TAMP_IRQn, STM32_RTC_TAMP_IRQn_PRIORITY);
#endif // STM32_ENABLE_RTC_TAMP_IRQn

#if STM32_ENABLE_FLASH_IRQn
    NVIC_INIT(FLASH_IRQn, STM32_FLASH_IRQn_PRIORITY);
#endif // STM32_ENABLE_FLASH_IRQn
}

static inline void
exti_init()
{
#if STM32_ENABLE_EXTI0_1_IRQn
    NVIC_INIT(EXTI0_1_IRQn, STM32_EXTI0_1_IRQn_PRIORITY);
#endif // STM32_ENABLE_EXTI0_1_IRQn

#if STM32_ENABLE_EXTI2_3_IRQn
    NVIC_INIT(EXTI2_3_IRQn, STM32_EXTI2_3_IRQn_PRIORITY);
#endif // STM32_ENABLE_EXTI2_3_IRQn

#if STM32_ENABLE_EXTI4_15_IRQn
    NVIC_INIT(EXTI4_15_IRQn, STM32_EXTI4_15_IRQn_PRIORITY);
#endif // STM32_ENABLE_EXTI4_15_IRQn
}

static inline void
dma_init()
{
#if STM32_ENABLE_DMA1_Channel1_IRQn
    NVIC_INIT(DMA1_Channel1_IRQn, STM32_DMA1_Channel1_IRQn_PRIORITY);
#endif // STM32_ENABLE_DMA1_Channel1_IRQn

#if STM32_ENABLE_DMA1_Channel2_3_IRQn
    NVIC_INIT(DMA1_Channel2_3_IRQn, STM32_DMA1_Channel2_3_PRIORITY);
#endif // STM32_ENABLE_DMA1_Channel2_3_IRQn

#if STM32_ENABLE_DMA1_Ch4_5_DMAMUX1_OVR_IRQn
    NVIC_INIT(DMA1_Ch4_5_DMAMUX1_OVR_IRQn, STM32_Channel4_5_DMAMUx1_OVR_IRQn_PRIORITY);
#endif // STM32_ENABLE_DMA1_Ch4_5_DMAMUX1_OVR_IRQn
}

static inline void
adc_init()
{
#if STM32_ENABLE_ADC1_IRQn
    NVIC_INIT(ADC1_IRQn, STM32_ADC1_IRQn_PRIORITY);
#endif // STM32_ENABLE_ADC1_IRQn
}

static inline void
timer_init()
{
#if STM32_ENABLE_TIM1_BRK_UP_TRG_COM_IRQn
    NVIC_INIT(TIM1_BRK_UP_TRG_COM_IRQn, STM32_TIM1_BRK_UP_TRG_COM_IRQn_PRIORITY);
#endif // STM32_ENABLE_TIM1_BRK_UP_TRG_COM_IRQn

#if STM32_ENABLE_TIM1_CC_IRQn
    NVIC_INIT(TIM1_CC_IRQn, STM32_TIM1_CC_IRQn_PRIORITY);
#endif // STM32_ENABLE_TIM1_CC_IRQn

#if STM32_ENABLE_TIM2_IRQn
    NVIC_INIT(TIM2_IRQn, STM32_TIM2_IRQn_PRIORITY);
#endif // STM32_ENABLE_TIM2_IRQn

#if STM32_ENABLE_TIM3_IRQn
    NVIC_INIT(TIM3_IRQn, STM32_TIM3_IRQn_PRIORITY);
#endif // STM32_ENABLE_TIM3_IRQn

#if STM32_ENABLE_LPTIM1_IRQn
    NVIC_INIT(LPTIM1_IRQn, STM32_LPTIM1_IRQn_PRIORITY);
#endif // STM32_ENABLE_LPTIM1_IRQn

#if STM32_ENABLE_LPTIM2_IRQn
    NVIC_INIT(LPTIM2_IRQn, STM32_LPTIM2_IRQn_PRIORITY);
#endif // STM32_ENABLE_LPTIM2_IRQn

#if STM32_ENABLE_TIM14_IRQn
    NVIC_INIT(TIM14_IRQn, STM32_TIM14_IRQn_PRIORITY);
#endif // STM32_ENABLE_TIM14_IRQn

#if STM32_ENABLE_TIM16_IRQn
    NVIC_INIT(TIM16_IRQn, STM32_TIM16_IRQn_PRIORITY);
#endif // STM32_ENABLE_TIM16_IRQn

#if STM32_ENABLE_TIM17_IRQn
    NVIC_INIT(TIM17_IRQn, STM32_TIM17_IRQn_PRIORITY);
#endif // STM32_ENABLE_TIM17_IRQn
}

static inline void
i2c_init()
{
#if STM32_ENABLE_I2C1_IRQn
    NVIC_INIT(I2C1_IRQn, STM32_I2C1_IRQn_PRIORITY);
#endif // STM32_ENABLE_I2C1_IRQn

#if STM32_ENABLE_I2C2_IRQn
    NVIC_INIT(I2C2_IRQn, STM32_I2C2_IRQn_PRIORITY);
#endif // STM32_ENABLE_I2C2_IRQn
}

static inline void
spi_init()
{
#if STM32_ENABLE_SPI1_IRQn
    NVIC_INIT(SPI1_IRQn, STM32_SPI1_IRQn_PRIORITY);
#endif // STM32_ENABLE_SPI1_IRQn

#if STM32_ENABLE_SPI2_IRQn
    NVIC_INIT(SPI2_IRQn, STM32_SPI2_IRQn_PRIORITY);
#endif // STM32_ENABLE_SPI2_IRQn
}

static inline void
usart_init()
{
#if STM32_ENABLE_USART1_IRQn
    NVIC_INIT(USART1_IRQn, STM32_USART1_IRQn_PRIORITY);
#endif // STM32_ENABLE_USART1_IRQn

#if STM32_ENABLE_USART2_IRQn
    NVIC_INIT(USART2_IRQn, STM32_USART2_IRQn_PRIORITY);
#endif // STM32_ENABLE_USART2_IRQn

#if STM32_ENABLE_LPUART1_IRQn
    NVIC_INIT(LPUART1_IRQn, STM32_LPUART1_IRQn_PRIORITY);
#endif // STM32_ENABLE_LPUART1_IRQn
}

void
stm32_nvic_config()
{
    ungrouped_init();
    exti_init();
    adc_init();
    timer_init();
    i2c_init();
    spi_init();
    usart_init();
}

