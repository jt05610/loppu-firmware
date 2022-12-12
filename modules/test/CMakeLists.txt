message("loading tests")
if (CMAKE_BUILD_TYPE MATCHES Debug)

    set(
        DRIVER_TEST_SOURCE
        "../../drivers/timer/test/fakes/src/fake_timer.c"
        "../../drivers/serial/test/fakes/src/fake_serial.c"
        "../../drivers/serial/test/spies/src/serial_spy.c"
        "../../drivers/stepper/test/fakes/src/fake_stepper.c"
        "../../drivers/gpio/test/mocks/src/mock_gpio_c.c"
        "../../drivers/gpio/test/mocks/src/mock_gpio.cpp"
    )

    include_directories(
        ${CppUTest_SOURCE_DIR}/include
        ../../drivers/timer/test/fakes/inc/
        ../../drivers/timer/test/inc/
        ../../drivers/stepper/test/inc
        ../../drivers/stepper/test/fakes
        ../../drivers/gpio/test/mocks/inc
        ../../drivers/gpio/test/inc
    )
    add_subdirectory(gpio)
    add_subdirectory(timer)
    add_subdirectory(buttons)
    add_subdirectory(stepper)
    add_subdirectory(data_model)
    add_executable(all_tests all_tests.cpp)

    set(
        DRIVER_TEST_LIBS
        ${SERIAL_TEST_LIB}
        ${TIMER_TEST_LIB}
        ${GPIO_TEST_LIB}
        ${STEPPER_TEST_LIB}
        ${DATA_MODEL_TEST_LIB}
    )
    
    target_link_libraries(all_tests ${DRIVER_TEST_LIBS} CppUTest CppUTestExt)
endif()