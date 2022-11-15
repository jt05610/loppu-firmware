file(
    GLOB_RECURSE
    STEPPER_TEST_SRC
    *.cpp
    fakes/src/*.c
    ../../../src/stepper/*.c
)
set(A4988_CONFIG ON)
set(DIR_PIN 1)
set(DIR_PORT GPIO_PORT_A)
set(STEP_PIN 2)
set(STEP_PORT GPIO_PORT_A)
set(MS1_PIN 3)
set(MS2_PIN 9)
set(MS3_PIN 11)
set(MS_PORT GPIO_PORT_A)
set(ENABLE_PIN 6)
set(ENABLE_PORT GPIO_PORT_A)
set(SLEEP_PIN 7)
set(SLEEP_PORT GPIO_PORT_A)
set(RESET_PIN 8)
set(RESET_PORT GPIO_PORT_A)

configure_file(${DRIVERS_ROOT_DIR}/inc/stepper/a4988_config.h.in a4988_config.h @ONLY)

add_library(
    "${STEPPER_TEST_LIB}"
    "${STEPPER_TEST_SRC}"
)

include_directories(
    ${DRIVERS_ROOT_DIR}/inc/
    fakes/inc
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(
    "${STEPPER_TEST_LIB}"
    "${GPIO_LIB}"
    "${TIMER_LIB}"
)
add_executable(StepperTests all_tests.cpp)

target_link_libraries(
    StepperTests
    PRIVATE
    ${STEPPER_TEST_LIB}
    CppUTest
    CppUTestExt
)
