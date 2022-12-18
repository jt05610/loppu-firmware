/**
  ******************************************************************************
  * @file   adc_config.h
  * @author Jonathan Taylor
  * @date   12/16/22
  * @brief  Configuration macros for STM32G031xx ADC peripheral.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#ifndef STM32_ADC_CONFIG_H
#define STM32_ADC_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup STM32G0xx_ADCConfig ADC config
 * @ingroup STM32G0xx_ADC
 * @ingroup STM32G0xx_DefaultConfig
 * @brief Default configuration for STM32G0xx
 * @{
 */

/**
 * @defgroup STM32G0xx_ADCConfig_Gen General ADC configuration
 * @brief Basic settings for ADC peripheral
 * @{
 */
#define STM32_ENABLE_ADC                1   /**< @brief Enable ADC peripheral */
#define STM32_ADC_BUFFER_SIZE           100 /**< @brief # of samples to store */
#define STM32_ADC_ENABLE_DMA            1   /**< @brief Enable DMA requests */

/** @brief Clock prescaler */
#define STM32_ADC_CLOCK                 LL_ADC_CLOCK_SYNC_PCLK_DIV2

/** @brief ADC resolution */
#define STM32_ADC_RESOLUTION            LL_ADC_RESOLUTION_12B

/** @brief Data alignment */
#define STM32_ADC_DATAALIGNMENT         LL_ADC_DATA_ALIGN_RIGHT

/** @brief Low power mode */
#define STM32_ADC_LOWPOWERMODE          LL_ADC_LP_MODE_NONE

/** @brief Sets sequencer as configurable */
#define STM32_ADC_SEQ_CONFIG            LL_ADC_REG_SEQ_CONFIGURABLE

/** @brief Sequencer rank for channel */
#define STM32_ADC_SEQUENCER_RANKS       LL_ADC_REG_RANK_1

/** @brief Sampling time */
#define STM32_ADC_SAMP_TIME             LL_ADC_SAMPLINGTIME_COMMON_1

/** @brief configure timeout during initialization */
#define STM32_ADC_USE_TIMEOUT           0

#if STM32_ADC_USE_TIMEOUT
/** @brief Timeout duration if used */
#define ADC_CHANNEL_CONF_RDY_TIMEOUT_MS 1U
#endif
/** @} */

/**
 * @defgroup STM32G0xx_ADCConfig_Conv ADC Regular conversion configuration
 * @brief Basic settings for ADC regular conversion
 * @{
 */

/** @brief External trigger conversion source */
#define STM32_ADC_TRIGGERSOURCE         LL_ADC_REG_TRIG_SOFTWARE

/** @brief When disabled, only channel with rank 1 is converted */
#define STM32_ADC_SEQUENCERLENGTH       LL_ADC_REG_SEQ_SCAN_DISABLE

/** @brief Enable sequencer discount */
#define STM32_ADC_SEQUENCERDISCONT      LL_ADC_REG_SEQ_DISCONT_DISABLE

/** @brief Enable or disable continuous conversion */
#define STM32_ADC_CONTINUOUSMODE        LL_ADC_REG_CONV_CONTINUOUS

/** @brief Enable DMA continuous transfers */
#define STM32_ADC_DMATRANSFER           LL_ADC_REG_DMA_TRANSFER_UNLIMITED

/** @brief Overrun behavior */
#define STM32_ADC_OVERRUN               LL_ADC_REG_OVR_DATA_OVERWRITTEN

/** @brief Oversampling mode */
#define STM32_ADC_OVERSAMPLINGSCOPE     LL_ADC_OVS_DISABLE

/** @brief Trigger frequency mode */
#define STM32_ADC_TRIGGERFREQUENCYMODE  LL_ADC_CLOCK_FREQ_MODE_HIGH

/** @brief Common sampling time group 1 */
#define STM32_ADC_SAMPLINGTIMECOMMON1   LL_ADC_SAMPLINGTIME_1CYCLE_5

/** @brief Common sampling time group 2 */
#define STM32_ADC_SAMPLINGTIMECOMMON2   LL_ADC_SAMPLINGTIME_1CYCLE_5
/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_ADC_InterruptConfig Interrupt events
 * @brief ADC interrupt generation configuration
 * @{
 */

/** Enable end of calibration interrupt generation */
#define STM32_ADC_ENABLE_IT_EOCAL       0

/** ADC ready interrupt generation */
#define STM32_ADC_ENABLE_IT_ADRDY       0

/** Enable end of conversion interrupt generation */
#define STM32_ADC_ENABLE_IT_EOC         0

/** Enable end of sequence of conversions interrupt generation */
#define STM32_ADC_ENABLE_IT_EOS         0

/** Enable analog watchdog 1 interrupt generation */
#define STM32_ADC_ENABLE_IT_AWD1        0

/** Enable analog watchdog 2 interrupt generation */
#define STM32_ADC_ENABLE_IT_AWD2        0

/** Enable analog watchdog 3 interrupt generation */
#define STM32_ADC_ENABLE_IT_AWD3        0

/** Enable channel configuration ready interrupt generation */
#define STM32_ADC_ENABLE_IT_CCRDY       0

/** Enable end of sampling phase interrupt generation */
#define STM32_ADC_ENABLE_IT_EOSMP       0

/** Enable overrun interrupt generation */
#define STM32_ADC_ENABLE_IT_OVR         0
/** @} */

/**
  ******************************************************************************
 * @defgroup STM32G0xx_ADC_WatchdogConfig ADC watchdog config
 * @brief ADC watchdog configuration
 * @{
 */

#define STM32_ADC_ENABLE_WD_1           0   /**< @brief Enable ADC watchdog 1 */
#define STM32_ADC_ENABLE_WD_2           0   /**< @brief Enable ADC watchdog 2 */
#define STM32_ADC_ENABLE_WD_3           0   /**< @brief Enable ADC watchdog 3 */

#ifdef STM32_ADC_ENABLE_WD_1
/** @brief Analog watchdog channel */
#define STM32_ADC_WD_MON_CHAN           LL_ADC_AWD_CHANNEL_0_REG

#endif // STM32_ADC_ENABLE_WD_1
/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif //STM32_ADC_CONFIG_H

#pragma clang diagnostic pop