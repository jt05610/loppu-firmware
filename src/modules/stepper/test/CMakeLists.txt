file(
    GLOB_RECURSE
    STEPPER_TEST_SRC
    *.cpp
    fakes/src/*.c
    ../../../src/stepper/*.c
)

add_library(
    "${STEPPER_TEST_LIB}"
    "${STEPPER_TEST_SRC}"
)

include_directories(
    ${DRIVERS_ROOT_DIR}/inc/
    fakes/inc
    ${CMAKE_CURRENT_BINARY_DIR}
    ../../../lib/drivers/gpio/test/fakes/inc
)

target_link_libraries(
    "${STEPPER_TEST_LIB}"
    "${STEPPER_LIB}"
    "${GPIO_TEST_LIB}"
    "${TIMER_TEST_LIB}"
)

add_executable(StepperTests all_tests.cpp)

target_link_libraries(
    StepperTests
    PRIVATE
    CppUTest
    ${STEPPER_TEST_LIB}
)
