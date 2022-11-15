//
// Created by Jonathan Taylor on 5/8/22.
//

#include "CppUTest/CommandLineTestRunner.h"

#include "serial_test_groups.h"
#include "timer_test_groups.h"
#include "gpio_test_groups.h"
#include "stepper_test_groups.h"

int main(int argc, char ** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
