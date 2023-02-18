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
#include "gpio.h"

#define IC_CHANNEL 0x00
#define SERVER_ADDR 0x00

static struct
{
    void * ser_inst;
    stepper_t            base;
    TMC2209TypeDef       ic;
    ConfigurationTypeDef cfg;

} self = {0};

#define _GPIO self.base.hal->gpio
#define _GPIO_PORT self.base.port

static inline void
_write_reg(uint8_t addr, uint8_t shift, uint8_t mask, int16_t val);

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
    self.base.vtable    = &interface;
    self.base.hal       = params->hal;
    self.base.port      = params->gpio_inst;
    self.ser_inst       = params->uart_inst;
    self.base.en_pin    = params->en_pin;
    self.base.tim_inst  = params->tim_inst;
    self.base.step_pin  = params->step_pin;
    self.base.dir_pin   = params->dir_pin;
    self.base.limit_pin = params->limit_pin;
    serial_open(self.base.hal->serial, self.ser_inst);
    tmc2209_setup();
    tmc_fillCRC8Table(0x07, true, 1);
    tmc2209_reset(&self.ic);
    gpio_init_pin(
            _GPIO, params->gpio_inst, params->en_pin,
            GPIO_PIN_MODE_NORMAL);
    gpio_init_pin(
            _GPIO, params->gpio_inst, params->dir_pin,
            GPIO_PIN_MODE_NORMAL);

    gpio_init_pin(
            _GPIO, params->gpio_inst, params->step_pin,
            GPIO_PIN_MODE_NORMAL);
    gpio_init_pin(
            _GPIO, params->gpio_inst, params->limit_pin,
            GPIO_PIN_MODE_INTERRUPT);


    tmc2209_set_mstep_reg(1);
    return &self.base;
}

#define _READ(addr, mask, shift) \
((tmc2209_readInt(&self.ic, (addr)) & (mask)) >> (shift))

#define READ(reg) \
_READ(TMC2209_##reg, TMC2209_##reg##_MASK, TMC2209_##reg##_SHIFT)

uint8_t
tmc2209_stepper_msg_count()
{
    return READ(IFCNT);
}

void
tmc2209_set_mstep_reg(uint8_t reg)
{
    _write_reg(
            TMC2209_GCONF,
            TMC2209_MSTEP_REG_SELECT_SHIFT,
            TMC2209_MSTEP_REG_SELECT_MASK,
            reg
    );
}

static inline uint8_t
get_dir()
{
    return gpio_read_pin(_GPIO, _GPIO_PORT, self.base.dir_pin);
}

static inline void
set_dir(uint8_t dir)
{
    void (* func)(GPIO base, gpio_port_t inst, gpio_pin_t pin);
    func = (dir > 0) ? gpio_set_pin : gpio_reset_pin;
    func(_GPIO, _GPIO_PORT, self.base.dir_pin);
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
    return (cc & TMC2209_MRES_MASK) >> TMC2209_MRES_SHIFT;
}

static inline void
set_microstep(microstep_t microstep)
{

}

static inline void
set_enabled(bool enabled)
{
    if (enabled) {
        gpio_reset_pin(_GPIO, _GPIO_PORT, self.base.en_pin);
    } else {
        gpio_set_pin(_GPIO, _GPIO_PORT, self.base.en_pin);
    }
}

static inline bool
get_enabled()
{
    return gpio_read_pin(_GPIO, _GPIO_PORT, self.base.en_pin);
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
    serial_read_write(
            self.base.hal->serial, self.ser_inst, data, writeLength, readLength);
    (void) channel;
}

uint8_t
tmc2209_CRC8(uint8_t * data, size_t length)
{
    return tmc_CRC8(data, length, 1);
}

static inline int16_t
_read_reg(uint8_t addr, uint8_t shift, uint8_t mask)
{

    uint32_t cc = tmc2209_readInt(&self.ic, addr);
    return (cc & mask) >> shift;
}

static inline void
_write_reg(uint8_t addr, uint8_t shift, uint8_t mask, int16_t val)
{
    int16_t cur = tmc2209_readInt(&self.ic, addr);
    cur &= ~mask;
    cur |= (val << shift) & mask;
    tmc2209_writeInt(&self.ic, addr, cur);
}
