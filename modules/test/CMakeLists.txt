message("loading tests")
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    include(FetchContent)
    set(TESTS OFF CACHE BOOL "Switch off CPPUTest Test build")
    fetchcontent_declare(
        CppUTest
        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
        GIT_TAG latest-passing-build
    )

    fetchcontent_makeavailable(CppUTest)

    set(SERIAL_TEST_LIB "${SERIAL_LIB}_test")
    set(TIMER_TEST_LIB "${TIMER_LIB}_test")
    set(GPIO_TEST_LIB "${GPIO_LIB}_test")
    set(STEPPER_TEST_LIB "${STEPPER_LIB}_test")
    set(BUTTONS_TEST_LIB "${BUTTONS_LIB}_test")

    set(
        DRIVER_TEST_SOURCE
        "timer/fakes/src/fake_timer.c"
        "serial/fakes/src/fake_serial.c"
        "serial/spies/src/serial_spy.c"
        "stepper/fakes/src/fake_stepper.c"
        "gpio/mocks/src/mock_gpio_c.c"
        "gpio/mocks/src/mock_gpio.cpp"
    )

    include_directories(
        ${CppUTest_SOURCE_DIR}/include
        timer/fakes/inc/
        timer/inc/
        stepper/inc
        stepper/fakes
        gpio/mocks/inc
        gpio/inc
    )
    add_subdirectory(gpio)
    add_subdirectory(timer)
    add_subdirectory(buttons)
    add_subdirectory(stepper)
    add_executable(all_tests all_tests.cpp)

    set(
        DRIVER_TEST_LIBS
        ${SERIAL_TEST_LIB}
        ${TIMER_TEST_LIB}
        ${GPIO_TEST_LIB}
        ${STEPPER_TEST_LIB}
    )
    
    target_link_libraries(all_tests ${DRIVER_TEST_LIBS} CppUTest CppUTestExt)
endif()