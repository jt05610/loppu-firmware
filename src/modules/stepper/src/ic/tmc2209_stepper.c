/**
  ******************************************************************************
  * @file   tmc2209_stepper.c
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


static struct {
    void *ser_inst;
    int32_t sg_thresh;
    int32_t cs_thresh;
    stepper_t base;
    TMC2209TypeDef ic;
    ConfigurationTypeDef cfg;
} self = {0};

#define _GPIO self.base.hal->gpio
#define _GPIO_PORT self.base.port

static inline void
_write_reg(uint8_t addr, uint16_t shift, int32_t mask, int32_t val);

static inline uint8_t get_dir();

static inline void set_dir(uint8_t dir);

static inline int32_t get_velocity();

static inline void set_velocity(int32_t value);

static inline microstep_t get_microstep();

static inline void set_microstep(microstep_t microstep);

static inline void set_enabled(bool enabled);

static inline bool get_enabled();

static inline void periodic_job();

static int32_t tstep_result();

static int32_t stall_result();


static stepper_interface_t interface = {
    .get_dir = get_dir,
    .set_dir = set_dir,
    .get_velocity = get_velocity,
    .set_velocity = set_velocity,
    .get_microstep = get_microstep,
    .set_microstep = set_microstep,
    .set_enabled = set_enabled,
    .get_enabled = get_enabled,
    .periodic_job = periodic_job,
    .get_tstep = tstep_result,
    .get_stall = stall_result
};

void
tmc2209_setup() {
    tmc2209_init(
        &self.ic,
        IC_CHANNEL,
        SERVER_ADDR,
        &self.cfg,
        &tmc2209_defaultRegisterResetState[0]
    );
}

Stepper
tmc2209_stepper_create(const tmc2209_init_t *params) {
    self.base.vtable = &interface;
    self.base.hal = params->hal;
    self.base.port = params->gpio_inst;
    self.ser_inst = params->uart_inst;
    self.base.en_pin = params->en_pin;
    self.base.tim_inst = params->tim_inst;
    self.base.step_pin = params->step_pin;
    self.base.dir_pin = params->dir_pin;
    self.base.limit_pin = params->limit_pin;
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

    serial_open(self.base.hal->serial, self.ser_inst);
    tmc2209_setup();
    tmc_fillCRC8Table(0x07, true, 1);
    tmc2209_reset(&self.ic);
    uint8_t i = tmc2209_stepper_msg_count();
    i++;
    while (tmc2209_stepper_msg_count() < i) {
        tmc2209_writeInt(
            &self.ic,
            TMC2209_GCONF,
            ((0x00 << TMC2209_I_SCALE_ANALOG_SHIFT) |
             (0x00 << TMC2209_INTERNAL_RSENSE_SHIFT) |
             (0x00 << TMC2209_EN_SPREADCYCLE_SHIFT) |
             (params->inverse_dir << TMC2209_SHAFT_SHIFT) |
             (0x00 << TMC2209_INDEX_OTPW_SHIFT) |
             (0x00 << TMC2209_INDEX_STEP_SHIFT) |
             (0x01 << TMC2209_PDN_DISABLE_SHIFT) |
             (0x01 << TMC2209_MSTEP_REG_SELECT_SHIFT) |
             (0x01 << TMC2209_MULTISTEP_FILT_SHIFT) |
             (0x00 << TMC2209_TEST_MODE_SHIFT))
        );
    }

    i++;
    while (tmc2209_stepper_msg_count() < i) {
        _write_reg(
            TMC2209_GCONF, TMC2209_MSTEP_REG_SELECT_SHIFT, TMC2209_MSTEP_REG_SELECT_MASK,
            0x01);
    }
    i++;
    while (tmc2209_stepper_msg_count() < i) {
        _write_reg(
            TMC2209_CHOPCONF, TMC2209_VSENSE_SHIFT, TMC2209_VSENSE_MASK,
            0x01);
    }
    i++;
    while (tmc2209_stepper_msg_count() < i) {
        _write_reg(
            TMC2209_COOLCONF, TMC2209_SEUP_SHIFT, TMC2209_SEUP_MASK, 0b11);
    }
    i++;
    while (tmc2209_stepper_msg_count() < i) {
        _write_reg(
            TMC2209_COOLCONF, TMC2209_SEMIN_SHIFT, TMC2209_SEMIN_MASK,
            0b0);
    }
    i++;
    while (tmc2209_stepper_msg_count() < i) {
        _write_reg(
            TMC2209_COOLCONF, TMC2209_SEMAX_SHIFT,
            TMC2209_SEMAX_MASK, 2);
    }

    i++;
    while (tmc2209_stepper_msg_count() < i) {
        tmc2209_set_cs_thresh_vel(params->cs_thresh);
    }
    tmc2209_set_t_pwm_thresh(0);
    tmc2209_set_sg_thresh(self.sg_thresh);
    stepper_set_enabled(&self.base, 0);
    return &self.base;
}

#define _READ(addr, mask, shift) \
((tmc2209_readInt(&self.ic, (addr)) & (mask)) >> (shift))

#define READ(reg) \
_READ(TMC2209_##reg, TMC2209_##reg##_MASK, TMC2209_##reg##_SHIFT)

uint8_t
tmc2209_stepper_msg_count() {
    return READ(IFCNT);
}

void
tmc2209_set_mstep_reg(uint8_t reg) {
    _write_reg(
        TMC2209_GCONF,
        TMC2209_MSTEP_REG_SELECT_SHIFT,
        TMC2209_MSTEP_REG_SELECT_MASK,
        reg
    );
}

int32_t tmc2209_sg_result() {
    return tmc2209_readInt(&self.ic, TMC2209_SG_RESULT);
}

int32_t tmc2209_tstep_result() {
    return _READ(TMC2209_TSTEP, TMC2209_TSTEP_MASK,
                 TMC2209_TSTEP_SHIFT);
}

void tmc2209_set_t_pwm_thresh(int32_t val) {
    _write_reg(
        TMC2209_TPWMTHRS, TMC2209_TPWMTHRS_SHIFT,
        TMC2209_TPWMTHRS_MASK,
        val);
}

void tmc2209_set_cs_thresh_vel(int32_t vel) {
    tmc2209_writeInt(&self.ic, TMC2209_TCOOLTHRS, vel);
}

void tmc2209_set_sg_thresh(int32_t val) {
    tmc2209_writeInt(&self.ic, TMC2209_SGTHRS, val);
}

void tmc2209_set_spreadcycle(bool value) {
    _write_reg(
        TMC2209_GCONF, TMC2209_EN_SPREADCYCLE_SHIFT,
        TMC2209_EN_SPREADCYCLE_MASK, value);
}

void tmc2209_set_internal_r_sense(bool value) {
    _write_reg(
        TMC2209_GCONF, TMC2209_INTERNAL_RSENSE_SHIFT,
        TMC2209_INTERNAL_RSENSE_MASK, value);
}

void tmc2209_set_pdn_disable(bool value) {
    _write_reg(
        TMC2209_GCONF, TMC2209_PDN_DISABLE_SHIFT,
        TMC2209_PDN_DISABLE_MASK,
        value);
}

void tmc2209_set_coolstep(bool value) {
    const uint8_t v = value ? 0b1111 : 0;
    _write_reg(TMC2209_COOLCONF, TMC2209_SEMIN_SHIFT, TMC2209_SEMIN_MASK, v);
}

static inline uint8_t
get_dir() {
    return gpio_read_pin(_GPIO, _GPIO_PORT, self.base.dir_pin);
}

static inline void
set_dir(uint8_t dir) {
    void (*func)(GPIO base, gpio_port_t inst, gpio_pin_t pin) = (dir > 0) ? gpio_set_pin : gpio_reset_pin;
    func(_GPIO, _GPIO_PORT, self.base.dir_pin);
}

static inline int32_t
get_velocity() {
    return tmc2209_readInt(&self.ic, TMC2209_VACTUAL);
}

static inline void
set_velocity(int32_t value) {
    tmc2209_writeInt(&self.ic, TMC2209_VACTUAL, value);
}

static inline microstep_t
get_microstep() {
    uint32_t cc = tmc2209_readInt(&self.ic, TMC2209_CHOPCONF);
    return 8 - ((cc & TMC2209_MRES_MASK) >> TMC2209_MRES_SHIFT);
}

static inline void
set_microstep(microstep_t microstep) {
    int16_t val = 0x08 - microstep;
    _write_reg(
        TMC2209_CHOPCONF, TMC2209_MRES_SHIFT, TMC2209_MRES_MASK,
        val);
}

static inline void
set_enabled(bool enabled) {
    if (enabled) {
        gpio_reset_pin(_GPIO, _GPIO_PORT, self.base.en_pin);
    } else {
        gpio_set_pin(_GPIO, _GPIO_PORT, self.base.en_pin);
    }
}

static inline bool
get_enabled() {
    return gpio_read_pin(_GPIO, _GPIO_PORT, self.base.en_pin);
}

static inline void
periodic_job() {
    tmc2209_periodicJob(&self.ic, 0);
}

int32_t tstep_result() {
    return tmc2209_tstep_result();
}

int32_t stall_result() {
    return tmc2209_sg_result();
}


void
tmc2209_readWriteArray(
    uint8_t channel, uint8_t *data, size_t writeLength,
    size_t readLength) {
    serial_read_write(
        self.base.hal->serial, self.ser_inst, data, writeLength,
        readLength);
    (void) channel;
}

uint8_t
tmc2209_CRC8(uint8_t *data, size_t length) {
    return tmc_CRC8(data, length, 1);
}

static inline int16_t
_read_reg(uint8_t addr, uint8_t shift, uint8_t mask) {
    uint32_t cc = tmc2209_readInt(&self.ic, addr);
    return (cc & mask) >> shift;
}

static inline void
_write_reg(uint8_t addr, uint16_t shift, int32_t mask, int32_t val) {
    int32_t cur = tmc2209_readInt(&self.ic, addr);
    cur &= ~mask;
    cur |= (val << shift) & mask;
    tmc2209_writeInt(&self.ic, addr, cur);
}
