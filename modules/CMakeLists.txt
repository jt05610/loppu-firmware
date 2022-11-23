set(SERIAL_LIB "serial")
set(GPIO_LIB "gpio")
set(TIMER_LIB "timer")
set(STEPPER_LIB "stepper")
set(BUTTONS_LIB "buttons")
set(DATA_MODEL_LIB "data_model")

set(DRIVERS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(
    DRIVER_TEST_INC
    ${DRIVERS_ROOT_DIR}/test/gpio/mocks/inc
    ${DRIVERS_ROOT_DIR}/test/serial/fakes/inc
    ${DRIVERS_ROOT_DIR}/test/serial/spies/inc
    ${DRIVERS_ROOT_DIR}/test/timer/fakes/inc
    ${DRIVERS_ROOT_DIR}/test/stepper/fakes/inc
)


file(
    GLOB_RECURSE
    DRIVER_SOURCE
    "${DRIVERS_ROOT_DIR}/src/*.*"
)

include_directories(inc)
add_subdirectory(src/serial)
add_subdirectory(src/gpio)
add_subdirectory(src/timer)
add_subdirectory(src/stepper)
add_subdirectory(src/buttons)
add_subdirectory(src/data_model)
#add_subdirectory(test)
