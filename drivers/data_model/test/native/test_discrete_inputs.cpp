//
// Created by taylojon on 11/23/2022.
//

#include "CppUTest/TestHarness.h"

#include "mock_gpio.h"

extern "C" {
#include "data_model/discrete_inputs.h"
#include "mock_gpio_c.h"

}

TEST_GROUP(discrete_inputs)
{
    gpio_t gpio;
    discrete_inputs_t inputs;

    void setup()
    {
        mock_gpio_create(&gpio);
        discrete_inputs_create(&inputs, &gpio);
    }

    void teardown()
    {
        mock_gpio_check_expectations();
        mock_gpio_destroy();
    }
    void _test_read(uint16_t address, gpio_pin_t pin)
    {
        mock_gpio_expect_read_pin(GPIO_PORT_A, pin, 0x00);
        discrete_inputs_read(&inputs, address);
    }
};

TEST(discrete_inputs, reads)
{
    uint16_t pins[] = {BTN_FORWARD_PIN, BTN_BACKWARD_PIN, BTN_INJECT_PIN};
    for (uint8_t i = 0; i < N_DISCRETE_INPUTS; i ++)
        _test_read(i, pins[i]);
}