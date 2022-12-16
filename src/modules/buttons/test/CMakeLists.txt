file(
    GLOB_RECURSE
    BUTTONS_TEST_SRC
    *.cpp
    fakes/src/*.c
    ../../../src/buttons/*.c
)

add_library(
    "${BUTTONS_TEST_LIB}"
    "${BUTTONS_TEST_SRC}"
)

include_directories(
    ${DRIVERS_ROOT_DIR}/inc/
    fakes/inc
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(
    "${BUTTONS_TEST_LIB}"
    "${BUTTONS_LIB}"
    "${GPIO_LIB}"
    "${TIMER_LIB}"
)
add_executable(ButtonsTests all_tests.cpp)

target_link_libraries(
    ButtonsTests
    PRIVATE
    ${BUTTONS_TEST_LIB}
    CppUTest
    CppUTestExt
)
