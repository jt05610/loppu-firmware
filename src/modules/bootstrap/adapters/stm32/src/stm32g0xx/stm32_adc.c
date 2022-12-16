/**
  ******************************************************************************
  * @file   stm32_adc.cpp
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32_adc.h"
#include "stm32g0xx_ll_adc.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32_dma.h"

static inline void start(void * data);

static inline void stop(void * data);

static inline void add_watchdog(uint8_t data, ADCWatchdog wd);

static adc_interface_t interface = {
        .start=start,
        .stop=stop,
        .add_watchdog=add_watchdog
};

static struct
{
    adc_base_t base;

}                      self      = {0};

static inline void
start(void * data)
{
    (void) data;
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, ADC_BUFFER_SIZE);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
    while(!LL_DMA_IsEnabledChannel(DMA1, LL_DMA_CHANNEL_2));
    LL_ADC_REG_StartConversion(ADC1);
}

static inline void
stop_conversion()
{
    LL_ADC_REG_StopConversion(ADC1);
    while (LL_ADC_REG_IsStopConversionOngoing(ADC1));
}

static inline void
stop(void * data)
{
    (void) data;
    LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
    while(LL_DMA_IsEnabledChannel(DMA1, LL_DMA_CHANNEL_2));
    LL_ADC_Disable(ADC1);
    while(LL_ADC_IsEnabled(ADC1));
}

static inline void
add_watchdog(uint8_t which, ADCWatchdog wd)
{
    uint32_t awd;
    void (* func)(ADC_TypeDef *);
    if ((uint8_t) which == 0) {
        awd  = LL_ADC_AWD1;
        func = LL_ADC_EnableIT_AWD1;
    } else if ((uint8_t) which == 1) {
        awd  = LL_ADC_AWD2;
        func = LL_ADC_EnableIT_AWD2;
    } else if ((uint8_t) which == 2) {
        awd  = LL_ADC_AWD3;
        func = LL_ADC_EnableIT_AWD3;
    } else {
        return;
    }
    stop(0);
    LL_ADC_ConfigAnalogWDThresholds(ADC1, awd, wd->max_value, wd->min_value);
    func(ADC1);
    start(0);
}

static inline void
calibrate()
{


}
Analog
stm32_adc_create()
{
    self.base.vtable                          = &interface;
    self.base.n_samples                       = ADC_BUFFER_SIZE;
    self.base.buffer                          = adc_buffer;
    LL_ADC_InitTypeDef     ADC_InitStruct     = {0};
    LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};

    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_SYSCLK);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC);

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /**ADC1 GPIO Configuration
    PA0   ------> ADC1_IN0
    */
    GPIO_InitStruct.Pin  = LL_GPIO_PIN_0;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    stm32_dma_params_t dma_params = {
            .dma=DMA1,
            .channel=LL_DMA_CHANNEL_2,
            .periph_address=LL_ADC_DMA_GetRegAddr(ADC1, 0),
            .memory_address=(uint32_t) adc_buffer,
            .data_length=self.base.n_samples,
            .transfer_direction=LL_DMA_DIRECTION_PERIPH_TO_MEMORY,
            .byte=false,
            .circular=true,
            .periph_request=LL_DMAMUX_REQ_ADC1,
            .enable_ht=false,
            .enable_tc=false
    };
    stm32_dma_init(&dma_params);
#define ADC_CHANNEL_CONF_RDY_TIMEOUT_MS ( 1U)
#if (USE_TIMEOUT == 1)
    uint32_t Timeout ; /* Variable used for Timeout management */
#endif /* USE_TIMEOUT */

    ADC_InitStruct.Clock         = LL_ADC_CLOCK_SYNC_PCLK_DIV2;
    ADC_InitStruct.Resolution    = LL_ADC_RESOLUTION_12B;
    ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
    ADC_InitStruct.LowPowerMode  = LL_ADC_LP_MODE_NONE;
    LL_ADC_Init(ADC1, &ADC_InitStruct);
    LL_ADC_REG_SetSequencerConfigurable(ADC1, LL_ADC_REG_SEQ_CONFIGURABLE);

    /* Poll for ADC channel configuration ready */
#if (USE_TIMEOUT == 1)
    Timeout = ADC_CHANNEL_CONF_RDY_TIMEOUT_MS;
#endif /* USE_TIMEOUT */
    while (LL_ADC_IsActiveFlag_CCRDY(ADC1) == 0) {
#if (USE_TIMEOUT == 1)
        /* Check Systick counter flag to decrement the time-out value */
   if (LL_SYSTICK_IsActiveCounterFlag())
     {
   if(Timeout-- == 0)
         {
   Error_Handler();
         }
     }
#endif /* USE_TIMEOUT */
    }
    /* Clear flag ADC channel configuration ready */
    LL_ADC_ClearFlag_CCRDY(ADC1);
    ADC_REG_InitStruct.TriggerSource    = LL_ADC_REG_TRIG_SOFTWARE;
    ADC_REG_InitStruct.SequencerLength  = LL_ADC_REG_SEQ_SCAN_DISABLE;
    ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
    ADC_REG_InitStruct.ContinuousMode   = LL_ADC_REG_CONV_CONTINUOUS;
    ADC_REG_InitStruct.DMATransfer      = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
    ADC_REG_InitStruct.Overrun          = LL_ADC_REG_OVR_DATA_OVERWRITTEN;
    LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
    LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
    LL_ADC_SetTriggerFrequencyMode(ADC1, LL_ADC_CLOCK_FREQ_MODE_HIGH);
    LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_COMMON_1,
                                         LL_ADC_SAMPLINGTIME_1CYCLE_5);
    LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_COMMON_2,
                                         LL_ADC_SAMPLINGTIME_1CYCLE_5);
    LL_ADC_ClearFlag_EOC(ADC1);
    LL_ADC_EnableIT_EOC(ADC1);
    LL_ADC_ClearFlag_EOS(ADC1);
    LL_ADC_DisableIT_EOS(ADC1);
    LL_ADC_ClearFlag_OVR(ADC1);
    LL_ADC_EnableIT_OVR(ADC1);
    /* Enable ADC internal voltage regulator */
    LL_ADC_EnableInternalRegulator(ADC1);
    /* Delay for ADC internal voltage regulator stabilization. */
    /* Compute number of CPU cycles to wait for, from delay in us. */
    /* Note: Variable divided by 2 to compensate partially */
    /* CPU processing cycles (depends on compilation optimization). */
    /* Note: If system core clock frequency is below 200kHz, wait time */
    /* is only a few CPU processing cycles. */
    uint32_t wait_loop_index;
    wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US *
                        (SystemCoreClock / (100000 * 2))) / 10);
    while (wait_loop_index != 0) {
        wait_loop_index--;
    }
    LL_ADC_SetAnalogWDMonitChannels(ADC1, LL_ADC_AWD1,
                                    LL_ADC_AWD_CHANNEL_0_REG);
    /** Configure Regular Channel
    */
    LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_0);
    LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_0,
                                  LL_ADC_SAMPLINGTIME_COMMON_1);
    /* USER CODE BEGIN ADC1_Init 2 */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    LL_ADC_StartCalibration(ADC1);
    while(LL_ADC_IsCalibrationOnGoing(ADC1));
    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
    while(LL_ADC_REG_GetDMATransfer(ADC1) != LL_ADC_REG_DMA_TRANSFER_UNLIMITED);
    LL_ADC_Enable(ADC1);
    while(!LL_ADC_IsEnabled(ADC1));

    /* DMA interrupt init */
    /* DMA1_Channel1_IRQn interrupt configuration */
    NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    /* DMA1_Channel2_3_IRQn interrupt configuration */
    /* USER CODE END ADC1_Init 2 */
    return &self.base;
}

