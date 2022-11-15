set(
    TIMER_TEST_HEADERS
    fakes/inc/fake_timer.h
    fakes/inc/fake_pwm.h
)

set(
    TIMER_TEST_SRC
    fake_pwm_test.cpp
    fake_timer_test.cpp
    win_timer_test.cpp
    posix_timer_test.cpp
    pwm_test.cpp
    fakes/src/fake_timer.c
    fakes/src/fake_pwm.c
)

add_library(
    "${TIMER_TEST_LIB}"
    "${TIMER_TEST_HEADERS}"
    "${TIMER_TEST_SRC}"
)

include_directories(
    fakes/inc
    ${DRIVERS_ROOT_DIR}/inc/
)

target_link_libraries(${TIMER_TEST_LIB} ${TIMER_LIB})

add_executable(TimerTests all_tests.cpp)

target_link_libraries(
    TimerTests
    PRIVATE
    ${TIMER_TEST_LIB}
    CppUTest
    CppUTestExt
)
