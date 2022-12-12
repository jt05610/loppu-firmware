add_subdirectory(buttons/src)
add_subdirectory(data_model/src)
add_subdirectory(gpio/src)
add_subdirectory(modbus)
add_subdirectory(serial/src)
add_subdirectory(stepper/src)
add_subdirectory(timer/src)

set(
    ${DRIVER_INC}
    buttons/inc
    data_model/inc
    gpio/inc
    modbus/inc
    serial/inc
    stepper/inc
    timer/inc
)

include_directories(${DRIVER_INC})

if (${BUILD_TESTS})
    include(FetchContent)
    set(TESTS OFF CACHE BOOL "Switch off CPPUTest Test build")

    set(BUTTONS_TEST_LIB buttons_test)
    set(DATA_MODEL_TEST_LIB data_model_test)
    set(GPIO_TEST_LIB gpio_test)
    set(MODBUS_TEST_LIB modbus_test)
    set(SERIAL_TEST_LIB serial_test)
    set(STEPPER_TEST_LIB stepper_test)
    set(TIMER_TEST_LIB timer_test)

    FetchContent_Declare(
        CppUTest
        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
        GIT_TAG latest-passing-build
    )

    FetchContent_MakeAvailable(CppUTest)
    include_directories(${CppUTest_SOURCE_DIR}/include)
    add_subdirectory(buttons/test)
    add_subdirectory(data_model/test)
    add_subdirectory(gpio/test)
    add_subdirectory(modbus/test)
    add_subdirectory(serial/test)
    add_subdirectory(stepper/test)
    add_subdirectory(timer/test)

endif()

