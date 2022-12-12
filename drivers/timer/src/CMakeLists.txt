set(TIMER_SOURCES timer.c pwm.c win_timer.c posix_timer.c)

include_directories(../inc)

add_library(
    ${TIMER_LIB}
    "${TIMER_SOURCES}"
)
