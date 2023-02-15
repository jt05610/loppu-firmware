/**
  ******************************************************************************
  * @file   stm32_adc.cpp
  * @author Jonathan Taylor
  * @date   12/15/22
  * @brief  STM32 ADC peripheral implementation.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_adc.h"

#include "stm32_adc.h"
#include "default/adc_config.h"
#include "stm32_interrupts.h"
#include "helper_macros.h"
#include "stm32_dma.h"
#include "default/dma_config.h"
#include "advanced/adc_adv_config.h"

static struct
{
    adc_base_t base;
    uint16_t   adc_buffer[STM32_ADC_BUFFER_SIZE];

} self = {0};

static inline void start();

static inline void stop();

static inline void calibrate();

static inline void add_watchdog(ADCWatchdog wd);

static inline void adc_init();

static inline void adc_reg_init();

static inline void adc_isr_init();

static inline void adc_regulator_init();

static inline void adc_channel_init();

static adc_interface_t interface = {
        .start=start,
        .stop=stop,
        .add_watchdog=add_watchdog
};

Analog
stm32_adc_create()
{
    self.base.vtable    = &interface;
    self.base.n_samples = STM32_ADC_BUFFER_SIZE;
    self.base.buffer    = self.adc_buffer;

    adc_init();
    adc_reg_init();
    adc_isr_init();
    adc_regulator_init();
    adc_channel_init();
    calibrate();

#if STM32_ADC_ENABLE_DMA
    LL_ADC_REG_SetDMATransfer(ADC1, STM32_ADC_DMATRANSFER);
#endif
    LL_ADC_Enable(ADC1);

    while (!LL_ADC_IsEnabled(ADC1));

    return &self.base;
}

volatile uint16_t * stm32_adc_get_buffer()
{
    return self.adc_buffer;
}

static inline void
start()
{
    stm32_dma_start_channel(STM32_ADC_DMA_CHANNEL);
    LL_ADC_REG_StartConversion(ADC1);
}

static inline void
stop()
{
    LL_ADC_REG_StopConversion(ADC1);
    while (LL_ADC_REG_IsStopConversionOngoing(ADC1));
}

static inline void
add_watchdog(ADCWatchdog wd)
{
    stop();
    if ((uint8_t) wd->data == 0) {
        LL_ADC_ConfigAnalogWDThresholds(ADC1, LL_ADC_AWD1, wd->max_value,
                                        wd->min_value);
        LL_ADC_EnableIT_AWD1(ADC1);
    } else if ((uint8_t) wd->data == 1) {
        LL_ADC_ConfigAnalogWDThresholds(ADC1, LL_ADC_AWD2, wd->max_value,
                                        wd->min_value);
        LL_ADC_EnableIT_AWD2(ADC1);
    } else if ((uint8_t) wd->data == 2) {
        LL_ADC_ConfigAnalogWDThresholds(ADC1, LL_ADC_AWD3, wd->max_value,
                                        wd->min_value);
        LL_ADC_EnableIT_AWD3(ADC1);
    } else {
        return;
    }
    start();
}

static inline void
calibrate()
{
    /* USER CODE BEGIN ADC1_Init 2 */
    LL_ADC_StartCalibration(ADC1);
    while (LL_ADC_IsCalibrationOnGoing(ADC1));
}

static inline void
adc_init()
{
    LL_ADC_InitTypeDef ADC_InitStruct = {0};

#if STM32_ADC_USE_TIMEOUT
    uint32_t Timeout ; /* Variable used for Timeout management */
#endif // STM32_ADC_USE_TIMEOUT

    ADC_InitStruct.Clock         = STM32_ADC_CLOCK;
    ADC_InitStruct.Resolution    = STM32_ADC_RESOLUTION;
    ADC_InitStruct.DataAlignment = STM32_ADC_DATAALIGNMENT;
    ADC_InitStruct.LowPowerMode  = STM32_ADC_LOWPOWERMODE;

    LL_ADC_Init(ADC1, &ADC_InitStruct);

    LL_ADC_REG_SetSequencerConfigurable(ADC1, STM32_ADC_SEQ_CONFIG);

    /* Poll for ADC channel configuration ready */
#if STM32_ADC_USE_TIMEOUT
#include "stm32_interrupts.h"
    Timeout = ADC_CHANNEL_CONF_RDY_TIMEOUT_MS;
#endif // STM32_ADC_USE_TIMEOUT
    while (LL_ADC_IsActiveFlag_CCRDY(ADC1) == 0) {
#if STM32_ADC_USE_TIMEOUT
        /* Check Systick counter flag to decrement the time-out value */
        if (LL_SYSTICK_IsActiveCounterFlag()) {
            if (Timeout-- == 0) {
                Error_Handler();
            }
        }
#endif // STM32_ADC_USE_TIMEOUT
    }

    /* Clear flag ADC channel configuration ready */
    LL_ADC_ClearFlag_CCRDY(ADC1);
}

static inline void
adc_reg_init()
{
    LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};


    ADC_REG_InitStruct.TriggerSource    = STM32_ADC_TRIGGERSOURCE;
    ADC_REG_InitStruct.SequencerLength  = STM32_ADC_SEQUENCERLENGTH;
    ADC_REG_InitStruct.SequencerDiscont = STM32_ADC_SEQUENCERDISCONT;
    ADC_REG_InitStruct.ContinuousMode   = STM32_ADC_CONTINUOUSMODE;
    ADC_REG_InitStruct.DMATransfer      = STM32_ADC_DMATRANSFER;
    ADC_REG_InitStruct.Overrun          = STM32_ADC_OVERRUN;

    LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
    LL_ADC_SetOverSamplingScope(ADC1, STM32_ADC_OVERSAMPLINGSCOPE);
    LL_ADC_SetTriggerFrequencyMode(ADC1, STM32_ADC_TRIGGERFREQUENCYMODE);
    LL_ADC_SetSamplingTimeCommonChannels(
            ADC1,
            LL_ADC_SAMPLINGTIME_COMMON_1,
            STM32_ADC_SAMPLINGTIMECOMMON1
    );
    LL_ADC_SetSamplingTimeCommonChannels(
            ADC1,
            LL_ADC_SAMPLINGTIME_COMMON_2,
            STM32_ADC_SAMPLINGTIMECOMMON2
    );
}

static inline void
adc_isr_init()
{
    ADC1_ISR_INIT(EOS);
    ADC1_ISR_INIT(OVR);
#if 0
    ADC1_ISR_INIT(EOCAL);
    ADC1_ISR_INIT(ADRDY);
    ADC1_ISR_INIT(EOC);
    ADC1_ISR_INIT(AWD1);
    ADC1_ISR_INIT(AWD2);
    ADC1_ISR_INIT(AWD3);
    ADC1_ISR_INIT(CCRDY);
    ADC1_ISR_INIT(EOSMP);
#endif
}

static inline void
adc_regulator_init()
{
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
}

static inline void
adc_channel_init()
{
    /* TODO Correct sequencer rank logic */

    LL_ADC_SetAnalogWDMonitChannels(
            ADC1, LL_ADC_AWD1, STM32_ADC_WD_MON_CHAN
    );
    LL_ADC_REG_SetSequencerRanks(
            ADC1, STM32_ADC_SEQUENCER_RANKS, LL_ADC_CHANNEL_0
    );
    LL_ADC_SetChannelSamplingTime(
            ADC1, LL_ADC_CHANNEL_0, STM32_ADC_SAMP_TIME
    );
}

#define __ISR_HANDLE(flag) if(LL_ADC_IsActiveFlag_##flag)

__INTERRUPT
ADC1_IRQHandler()
{
#if STM32_ADC_ENABLE_IT_EOCAL
    __HANDLE(EOCAL) {

    }
    __CLEAR_FLAG(_ADC, ADC1, EOCAL);
#endif

#if STM32_ADC_ENABLE_IT_ADRDY
    __HANDLE(ADRDY) {

    }
    __CLEAR_FLAG(_ADC, ADC1, ADRDY);
#endif

#if STM32_ADC_ENABLE_IT_EOC
    __HANDLE(EOC) {

    }
    __CLEAR_FLAG(_ADC, ADC1, EOC);
#endif

#if STM32_ADC_ENABLE_IT_EOS
    __HANDLE(EOS) {

    }
    __CLEAR_FLAG(_ADC, ADC1, EOS);
#endif

#if STM32_ADC_ENABLE_IT_AWD1
    __HANDLE(AWD1) {

    }
    __CLEAR_FLAG(_ADC, ADC1, AWD1);
#endif

#if STM32_ADC_ENABLE_IT_AWD2
    __HANDLE(AWD2) {

    }
    __CLEAR_FLAG(_ADC, ADC1, AWD2);
#endif

#if STM32_ADC_ENABLE_IT_AWD3
    __HANDLE(AWD3) {

    }
    __CLEAR_FLAG(_ADC, ADC1, AWD3);
#endif

#if STM32_ADC_ENABLE_IT_CCRDY
    __HANDLE(CCRDY) {

    }
    __CLEAR_FLAG(_ADC, ADC1, CCRDY);
#endif

#if STM32_ADC_ENABLE_IT_EOSMP
    __HANDLE(EOSMP) {

    }
    __CLEAR_FLAG(_ADC, ADC1, EOSMP);
#endif

#if STM32_ADC_ENABLE_IT_OVR
    __HANDLE(OVR) {

    }
    __CLEAR_FLAG(_ADC, ADC1, OVR);
#endif

}

