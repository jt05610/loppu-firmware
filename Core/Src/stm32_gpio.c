#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_gpio.h"
#include "stm32g0xx_it.h"
#include "stm32_gpio.h"

#define EXTI_PORT(port) \
((port == GPIO_PORT_A)) ? LL_EXTI_CONFIG_PORTA : LL_EXTI_CONFIG_PORTB

#define PERIPH(port) \
((port) == GPIO_PORT_A) ? LL_IOP_GRP1_PERIPH_GPIOA : LL_IOP_GRP1_PERIPH_GPIOB

static struct
{
    handler_t gpio_interrupt;
} self = {0};

static inline void set_pin(gpio_port_t port, gpio_pin_t pin);

static inline void reset_pin(gpio_port_t port, gpio_pin_t pin);

static inline uint32_t read_port(gpio_port_t port);

static inline uint8_t read_pin(gpio_port_t port, gpio_pin_t pin);

static inline void write_port(gpio_port_t port, uint32_t value);

static inline void toggle(gpio_port_t port, gpio_pin_t pin);

static inline void init_exti(pin_init_t * init);

static inline bool validate_pin_init(pin_init_t * init);

static inline void init_single_pin(uint32_t current_pin, pin_init_t * init);

static inline void init_normal_pin(pin_init_t * init);

static gpio_interface_t interface = {
        .set_pin = set_pin,
        .reset_pin = reset_pin,
        .read_port = read_port,
        .read_pin = read_pin,
        .write_port = write_port,
        .toggle = toggle
};

void
stm32_gpio_create(GPIO base)
{
    base->vtable = &interface;
}


void
stm32_gpio_init_pin(pin_init_t * init)
{
    if (validate_pin_init(init))
        switch (init->type)
        {
            case NormalPin:
                init_normal_pin(init);
                break;
            case InterruptPin:
                init_exti(init);
                break;
        }
}

static inline bool
validate_pin_init(pin_init_t * init)
{
    return IS_GPIO_ALL_INSTANCE(STM_PORT(init->port))
           && IS_LL_GPIO_PIN(init->pin_mask)
           && IS_LL_GPIO_MODE(init->mode);
}


static inline void
init_single_pin(uint32_t current_pin, pin_init_t * init)
{
    if (LL_GPIO_MODE_OUTPUT == init->mode
        || LL_GPIO_MODE_ALTERNATE == init->mode)
    {
        LL_GPIO_SetPinSpeed(
                STM_PORT(init->port), current_pin,
                LL_GPIO_SPEED_FREQ_LOW);
        LL_GPIO_SetPinOutputType(
                STM_PORT(init->port), current_pin,
                LL_GPIO_OUTPUT_PUSHPULL);
    }
    LL_GPIO_SetPinPull(STM_PORT(init->port), current_pin,
                       LL_GPIO_PULL_NO);
    LL_GPIO_SetPinMode(STM_PORT(init->port), current_pin, init->mode);
}

static inline void
init_normal_pin(pin_init_t * init)
{
    uint32_t pin_pos;
    uint32_t current_pin;

    LL_IOP_GRP1_EnableClock(PERIPH(init->port));

    pin_pos = 0;

    while ((init->pin_mask >> pin_pos) != 0x00U)
    {
        current_pin = init->pin_mask & (0x01U << pin_pos);
        if (0x00U != current_pin)
            init_single_pin(current_pin, init);

        pin_pos++;
    }
}


static inline void
init_exti(pin_init_t * init)
{
    LL_EXTI_InitTypeDef exti_init;
    exti_init.Line_0_31   = LL_EXTI_LINE_8;
    exti_init.LineCommand = ENABLE;
    exti_init.Mode        = LL_EXTI_MODE_IT;
    exti_init.Trigger     = init->trigger;

    LL_EXTI_SetEXTISource(EXTI_PORT(init->port), LL_EXTI_CONFIG_LINE8);
    LL_EXTI_Init(&exti_init);
    LL_GPIO_SetPinPull(STM_PORT(init->port), init->pin_mask, LL_GPIO_PULL_NO);
    LL_GPIO_SetPinMode(STM_PORT(init->port), init->pin_mask, init->mode);
    self.gpio_interrupt = init->handler;
    NVIC_SetPriority(EXTI4_15_IRQn, 0);
    NVIC_EnableIRQ(EXTI4_15_IRQn);
    LL_EXTI_EnableIT_0_31(LL_EXTI_CONFIG_LINE8);
}

static inline void
set_pin(gpio_port_t port, gpio_pin_t pin)
{
    LL_GPIO_SetOutputPin(STM_PORT(port), pin);
}

static inline void
reset_pin(gpio_port_t port, gpio_pin_t pin)
{
    LL_GPIO_ResetOutputPin(STM_PORT(port), pin);
}

static inline uint32_t
read_port(gpio_port_t port)
{
    return LL_GPIO_ReadInputPort(STM_PORT(port));
}

static inline uint8_t
read_pin(gpio_port_t port, gpio_pin_t pin)
{
    return LL_GPIO_IsOutputPinSet(STM_PORT(port), pin);
}

static inline void
write_port(gpio_port_t port, uint32_t value)
{
    LL_GPIO_WriteOutputPort(STM_PORT(port), value);
}

static inline void
toggle(gpio_port_t port, gpio_pin_t pin)
{
    LL_GPIO_TogglePin(STM_PORT(port), pin);
}

void
EXTI4_15_IRQHandler(void)
{
    if (LL_EXTI_IsActiveRisingFlag_0_31(LL_EXTI_LINE_8) != RESET)
    {
        LL_EXTI_ClearRisingFlag_0_31(LL_EXTI_LINE_8);
        if (self.gpio_interrupt)
            self.gpio_interrupt();
    }
}
