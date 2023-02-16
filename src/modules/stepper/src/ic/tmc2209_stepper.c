/**
  ******************************************************************************
  * @file   tmc2209_stepper.cpp
  * @author Jonathan Taylor
  * @date   11/17/22
  * @brief  DESCRIPTION
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 Jonathan Taylor.
  * All rights reserved.
  *
  ******************************************************************************
  */

#include "ic/tmc2209_stepper.h"
#include "TMC2209.h"

#define IC_CHANNEL 0x00
#define SERVER_ADDR 0x00

struct
{
    Serial serial;
    Timer  timer;
    void * ser_inst;
    void * tim_inst;
    stepper_t            base;
    TMC2209TypeDef       ic;
    ConfigurationTypeDef cfg;

} self = {0};

static inline uint8_t get_dir();

static inline void set_dir(uint8_t dir);

static inline int32_t get_velocity();

static inline void set_velocity(int32_t value);

static inline microstep_t get_microstep();

static inline void set_microstep(microstep_t microstep);

static inline void set_enabled(bool enabled);

static inline bool get_enabled();

static inline void periodic_job();

static stepper_interface_t interface = {
        .get_dir=get_dir,
        .set_dir=set_dir,
        .get_velocity=get_velocity,
        .set_velocity=set_velocity,
        .get_microstep=get_microstep,
        .set_microstep=set_microstep,
        .set_enabled=set_enabled,
        .get_enabled=get_enabled,
        .periodic_job=periodic_job,
};

void
tmc2209_setup()
{
    tmc2209_init(
            &self.ic,
            IC_CHANNEL,
            SERVER_ADDR,
            &self.cfg,
            &tmc2209_defaultRegisterResetState[0]
    );
}

Stepper
tmc2209_stepper_create(tmc2209_init_t * params)
{
    self.base.vtable = &interface;
    self.base.gpio   = params->hal->gpio;
    self.serial      = params->hal->serial;
    self.timer       = params->hal->timer;
    self.ser_inst    = params->uart_inst;
    self.tim_inst    = params->tim_inst;
    timer_reg_periodic_job(
            params->hal->timer,
            params->tim_inst,
            periodic_job,
            TMC2209_UPDATE_FREQ
    );
    tmc2209_setup();
    tmc_fillCRC8Table(0x07, true, 1);
    tmc2209_reset(&self.ic);
    timer_start(params->hal->timer, params->tim_inst, 115200);
    return &self.base;
}

uint8_t
tmc2209_stepper_msg_count()
{
    return tmc2209_readInt(&self.ic, TMC2209_IFCNT);
}

void
tmc2209_set_mstep_reg(uint8_t reg)
{
    int16_t v = tmc2209_readInt(&self.ic, TMC2209_GCONF);
    if (reg) {
        v |= 0x01 << TMC2209_MSTEP_REG_SELECT_SHIFT;
    } else {
        v &= ~(0x01 << TMC2209_MSTEP_REG_SELECT_SHIFT);
    }
    tmc2209_writeInt(&self.ic, TMC2209_GCONF, v);
}

static inline uint8_t
get_dir()
{

}

static inline void
set_dir(uint8_t dir)
{

}

static inline int32_t
get_velocity()
{
    return tmc2209_readInt(&self.ic, TMC2209_VACTUAL);
}

static inline void
set_velocity(int32_t value)
{
    tmc2209_writeInt(&self.ic, TMC2209_VACTUAL, value);
}

static inline microstep_t
get_microstep()
{
    uint32_t cc = tmc2209_readInt(&self.ic, TMC2209_CHOPCONF);
    return ( cc & TMC2209_MRES_MASK) >> TMC2209_MRES_SHIFT;
}

static inline void
set_microstep(microstep_t microstep)
{

}

static inline void
set_enabled(bool enabled)
{

}

static inline bool
get_enabled()
{
    return 0x01 == (tmc2209_readInt(&self.ic, TMC2209_IOIN) & TMC2209_ENN_MASK);
}

static inline void
periodic_job()
{
    tmc2209_periodicJob(&self.ic, 0);
}


void
tmc2209_readWriteArray(
        uint8_t channel, uint8_t * data, size_t writeLength, size_t readLength)
{
    serial_read_write(self.serial, self.ser_inst, data, writeLength, readLength);
}

uint8_t
tmc2209_CRC8(uint8_t * data, size_t length)
{
    return tmc_CRC8(data, length, 1);
}
