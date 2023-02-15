/**
  ******************************************************************************
  * @file   timer_private.h
  * @author Jonathan Taylor
  * @date   12/13/22
  * @brief  Timer abstract library private header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */


#ifndef DRIVERS_TIMER_PRIVATE_H
#define DRIVERS_TIMER_PRIVATE_H

#ifndef DRIVERS_TIMER_H
#include "timer.h"
#endif

/** @addtogroup Timer
 * @{
 */

/**
 * @brief When to call callbacks
 */
typedef enum callback_type_t
{
    Normal,                 /**< General callback after delay */
    RisingCallback,         /**< PWM rising callback */
    FallingCallback,        /**< PWM falling callback */
    RisingFallingCallback,  /**< PWM callback on both rising and falling */
} callback_type_t;

/**
 * @brief callback_t is a callback function which can be passed a void * for any
 *        data needed to process the callback.
 */
typedef void (* callback_t)(void * data);

/**
 * @brief Callback to be run at a given frequency
 */
typedef struct periodic_callback_t
{
    void * timer_instance;      /**< @brief Timer instance if needed. */
    uint32_t   on_tick;         /**< @brief Timer tick to run callback on. */
    callback_t cb;              /**< @brief Callback function to run. */
    void * data;                /**< @brief Any needed data for callback. */
    callback_type_t type;       /**< @brief Callback type. */
}            periodic_callback_t;

/**
 * @brief Timer interface functions
 */
typedef struct timer_interface_t
{
    /** @brief Starts timer */
    void (* start)(void * timer_instance, uint32_t freq);

    /** @brief Sets timeout */
    void (* set_timeout)(void * timer_instance, uint32_t timeout);

    /** @brief Stops timer */
    void (* stop)(void * timer_instance);

    /** @brief Gets timer tick */
    uint32_t (* get_tick)(void * timer_instance);

    /** @brief resets the passed timer */
    void (* reset)(void * timer_instance);

    /** @brief Starts microsecond timer */
    void (* start_us_timer)(void * timer_instance);

    /** @brief Stops microsecond timer */
    void (* stop_us_timer)(void * timer_instance);

    /** @brief delay function */
    void (* delay)(uint32_t millis);

    /** @brief delay in micros function */
    void (* delay_micros)(uint32_t micros);

    void (* reg_periodic_job)(void * tim_inst, void (*cb)(void), uint32_t freq);

    void (* reg_update_callback)(void * tim_inst, void (*cb)(void));

    void (* reg_pwm_callback)(void * tim_inst, void (*cb)(void));

    /** @brief tick count from microsecond timer if enabled */
    uint32_t (* micros)();

    /** @brief tick count in milliseconds from microsecond timer if enabled */
    uint32_t (* millis)();

    /** @brief set pwm frequency for specified timer instance */
    void (* set_pwm_freq)(void * timer_instance, uint32_t freq_Hz);

    /** @brief set pwm period for specified timer instance */
    void (* set_pwm_period)(void * timer_instance, uint32_t period);

    /** @brief set pwm duty cycle for specified timer instance */
    void (* set_pwm_duty_cycle)(void * timer_instance, uint16_t duty_cycle);

    /** @brief Sets pwm callback. */
    void (* set_pwm_callback)(PeriodicCallback cb, void * data);

    /** @brief Starts pwm and sets frequency and duty cycle if not already
     *         specified. */
    void (* start_pwm)(void * instance, uint32_t freq, uint16_t duty_cycle);

    /** @brief Stops pwm. */
    void (* stop_pwm)(void * instance);

} timer_interface_t;

/**
 * @brief Timer base struct
 */
typedef struct timer_base_t
{
    TimerInterface vtable; /**< @brief interface functions for timer */
} timer_base_t;

/** @} */

#endif //DRIVERS_TIMER_PRIVATE_H
