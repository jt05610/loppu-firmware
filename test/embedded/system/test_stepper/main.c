/**
  ******************************************************************************
  * @file   main.c
  * @author Jonathan Taylor
  * @date   2/14/23
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "TMC2209_eval/inc/tmc2209_eval.h"
#include "adapters/stm32/g031xx_adapter.h"
#include "stm32g031xx.h"
#include "ic/tmc2209_stepper.h"
#include "unity.h"

static Peripherals hal;
static Device      self;
static Stepper     stepper;

void
test_stepper_msg_cnt()
{
    tmc2209_stepper_msg_count();
}

void
test_set_velocity()
{
    stepper_set_velocity(stepper, 0);
}
void setUp()
{

}

void tearDown()
{
}

int
main()
{
    hal = bootstrap(stm32_dependency_injection, 0);

    tmc2209_init_t tmc_params = {.hal=hal, .tim_inst=TIM2, .uart_inst=USART2};
    stepper = tmc2209_stepper_create(&tmc_params);
    self    = tmc2209_eval_create(hal, USART1, TIM1, stepper);
    serial_open(hal->serial, USART1);
    serial_open(hal->serial, USART2);
    UNITY_BEGIN();
    RUN_TEST(test_set_velocity);
    RUN_TEST(test_stepper_msg_cnt);
    UNITY_END();
}


uint8_t
unity_output_char(char a)
{
    return serial_putchar(self->hal->serial, USART1, a);
}

void
unity_output_start()
{

}

void
unity_output_flush()
{

}

void
unity_output_complete()
{
    while (1);
}
