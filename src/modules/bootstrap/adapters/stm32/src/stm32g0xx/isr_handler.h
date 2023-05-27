/**
  ******************************************************************************
  * @file   isr_handler.h
  * @author Jonathan Taylor
  * @date   12/18/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#ifndef INJECTOR_ISR_HANDLER_H
#define INJECTOR_ISR_HANDLER_H

#define __ISR_HANDLE(periph, flag, channel) if(LL_##periph##_IsActiveFlag_##flag)
#define __CLEAR(flag, channel) LL_DMA_ClearFlag_##flag##channel
#define __CLEAR_FLAGS(channel)  __CLEAR(TC, channel); __CLEAR(TE, channel)

#define CREATE_ISR_HANDLER(periph, flag, t) \
void handle_##periph##_##flag(t data)

#define HANDLE(periph, flag)                \
    if(LL_##periph##_IsActiveFlag_##flag) { \
        handle_##periph##_##flag();         \
        LL_##periph##_ClearFlag_##flag;     \
    }                                       \
    while(LL_##periph##_IsActiveFlag_##flag)

#endif //INJECTOR_ISR_HANDLER_H
