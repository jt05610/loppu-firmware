/**
  ******************************************************************************
  * @file   timer.h
  * @author Jonathan Taylor
  * @date   12/13/22
  * @brief  Timer abstract library header.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */
#ifndef DRIVERS_TIMER_H
#define DRIVERS_TIMER_H

#include <stdint.h>

/** @addtogroup Peripherals
 *  @{
 */

/**
 * @defgroup Timer
 * @brief Timer abstraction library.
 * @details To implement a timer library for a given mcu, a timer_interface_t
 * must be implemented with definitions for the given function prototypes.
 * @{
 */

/**
 * @brief Timer is a pointer to a privately defined timer instance.
 */
typedef struct timer_base_t * Timer;

/**
 * @brief TimerInterface points to a struct of functions needed to implement
 *        a Timer on the target mcu.
 */
typedef struct timer_interface_t * TimerInterface;

/**
 * @brief PeriodicCallback points to a callback struct.
 */
typedef struct periodic_callback_t * PeriodicCallback;

/**
 * @defgroup General
 * @brief General timer functions.
 * @{
 */

/**
 * @brief Starts a timer with specified tick frequency.
 * @param self Timer instance.
 * @param timer_instance Timer instance if needed by target MCU.
 * @param freq Tick frequency in Hz.
 */
void timer_start(Timer self, void * timer_instance, uint32_t freq);

/**
 * @brief Stops the timer.
 * @param self Timer instance.
 * @param timer_instance Timer instance if needed by target MCU.
 */
void timer_stop(Timer self, void * timer_instance);

/**
 * @brief Gets the current tick count.
 * @param self Timer instance.
 * @param timer_instance timer instance of MCU if needed.
 * @return Current tick of timer.
 */
uint32_t timer_get_tick(Timer self, void * timer_instance);

/** @} */

/**
 * @defgroup Microsecond
 * @brief Provides functions for timing with microsecond precision.
 * @{
 */

/**
 * @brief Starts a timer with microsecond tick frequency.
 * @param self Timer instance.
 * @param timer_instance Any timer instance needed for the target mcu.
 */
void timer_start_microsecond_timer(Timer self, void * timer_instance);

/**
 * @brief Stops a previously started microsecond timer.
 * @param self Timer instance
 * @param timer_instance Any timer instance needed for the target mcu
 */
void timer_stop_microsecond_timer(Timer self, void * timer_instance);

/**
 * @brief Blocking delay for a microsecond period if microsecond timer is
 *        enabled.
 * @param self Timer instance.
 * @param microseconds Delay in microseconds.
 * @see timer_start_microsecond_timer
 */
void timer_delay_micros(Timer self, uint32_t microseconds);

/**
 * @brief Blocking delay for a millisecond period if a microsecond timer is
 *        enabled.
 * @param self Timer instance.
 * @param milliseconds Delay in milliseconds.
 * @see timer_start_microsecond_timer
 */
void timer_delay(Timer self, uint32_t milliseconds);

/**
 * @brief gets tick from microsecond timer if it was started with
 *        @ref timer_start_microsecond_timer.
 * @param self Timer instance.
 * @return Tick value from microsecond timer.
 * @see timer_start_microsecond_timer
 */
uint32_t timer_micros(Timer self);

/**
 * @brief Gets tick from microsecond timer if it was started with
 *        @ref timer_start_microsecond_timer and scales it to milliseconds.
 * @param self Timer instance.
 * @return Tick value from microsecond timer in milliseconds.
 * @see timer_start_microsecond_timer
 */
uint32_t timer_millis(Timer self);

/** @} */

/**
 * @defgroup PWM
 * @brief Functions to control pwm timers.
 * @{
 */

/**
* @brief Starts pwm timer.
* @param self Timer instance.
* @param pwm_instance PWM timer instance if needed by target mcu.
 * @param freq PWM frequency.
 * @param duty_cycle Desired duty cycle in e-3%. Value between 0 and 100000.
 *                   Scales between 0% and 100%.
*/
void timer_start_pwm(Timer self, void * pwm_instance, uint32_t freq, uint16_t duty_cycle);

/**
 * @brief Stops pwm timer.
 * @param self Timer instance.
 * @param pwm_instance PWM timer instance if needed by target mcu.
 */
void timer_stop_pwm(Timer self, void * pwm_instance);

/**
 * @brief Sets PWM frequency.
 * @param self Timer instance.
 * @param pwm_instance PWM timer instance if needed for target mcu.
 * @param freq PWM frequency.
 */
void timer_set_pwm_freq(Timer self, void * pwm_instance, uint32_t freq);

/**
 * @brief Sets duty cycle for pwm.
 * @param self Timer instance.
 * @param pwm_instance PWM timer instance if needed by target mcu.
 * @param duty_cycle Desired duty cycle in e-3%. Value between 0 and 100000.
 *                   Scales between 0% and 100%.
 */
void
timer_set_pwm_duty_cycle(Timer self, void * pwm_instance, uint16_t duty_cycle);

/**
 * @brief Sets pwm callback function.
 * @param self Timer instance.
 * @param cb PeriodicCallback to run.
 * @param data Any additional data needed.
 */
void timer_set_pwm_callback(Timer self, PeriodicCallback cb, void * data);

/** @} */

/** @} */

/** @} */

#include "timer_private.h"

#endif //DRIVERS_TIMER_H
