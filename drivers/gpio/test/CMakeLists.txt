set(
    GPIO_TEST_HEADERS
    fakes/inc/fake_gpio.h
    mocks/inc/mock_gpio.h
    mocks/inc/mock_gpio_c.h
)

set(
    GPIO_TEST_SRC
    fake_gpio_test.cpp
    fakes/src/fake_gpio.c
    mock_gpio_test.cpp
    mocks/src/mock_gpio.cpp
    mocks/src/mock_gpio_c.c
)


include_directories(
    fakes/inc
    mocks/inc
    ${DRIVERS_ROOT_DIR}/inc/
    inc
)

add_library(
    "${GPIO_TEST_LIB}"
    "${GPIO_TEST_SRC}"
)

target_link_libraries(
    ${GPIO_TEST_LIB}
    CppUTestExt
)
target_link_libraries(${GPIO_TEST_LIB} ${GPIO_LIB})

add_executable(GPIOTests all_tests.cpp)

target_link_libraries(
    GPIOTests
    PRIVATE
    ${GPIO_TEST_LIB}
    CppUTest
    CppUTestExt
)
