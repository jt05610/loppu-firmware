set(TIMER_INC_DIR ${DRIVERS_ROOT_DIR}/inc/timer)
set(TIMER_SOURCES timer.c pwm.c win_timer.c posix_timer.c)

set(
    TIMER_HEADERS
    ${TIMER_INC_DIR}/timer.h
    ${TIMER_INC_DIR}/.private/timer_private.h
    ${TIMER_INC_DIR}/pwm.h
)

add_library(
    "${TIMER_LIB}"
    "${DRIVERS_LIBRARY_TYPE}"
    "${TIMER_HEADERS}"
    "${TIMER_SOURCES}"
)

target_include_directories(
    ${TIMER_LIB}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../inc>
    $<INSTALL_INTERFACE:inc>
)


set_target_properties(
    "${TIMER_LIB}" PROPERTIES
    PUBLIC_HEADER "${TIMER_HEADERS}"
)

install(
    TARGETS "${TIMER_LIB}"
    EXPORT "${TIMER_LIB}"
    LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
    ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
    INCLUDES DESTINATION "${INC_INSTALL_DIR}/timer"
    PUBLIC_HEADER DESTINATION "${INC_INSTALL_DIR}/timer"
)
