set(STEPPER_INC_DIR ${DRIVERS_ROOT_DIR}/inc/stepper)

file(
    GLOB_RECURSE
    STEPPER_SOURCES
    *.c
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
)
set(
    STEPPER_HEADERS
    ${STEPPER_INC_DIR}/.private/stepper_private.h
    ${STEPPER_INC_DIR}/stepper.h
)

add_library(
    "${STEPPER_LIB}"
    "${DRIVERS_LIBRARY_TYPE}"
    "${STEPPER_HEADERS}"
    "${STEPPER_SOURCES}"
)

target_include_directories(
    ${STEPPER_LIB}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../inc>
    $<INSTALL_INTERFACE:inc>
)

set_target_properties(
    "${STEPPER_LIB}" PROPERTIES
    PUBLIC_HEADER "${STEPPER_HEADERS}"
)

target_link_libraries(
    ${STEPPER_LIB} ${GPIO_LIB} ${TIMER_LIB}
)

install(
    TARGETS "${STEPPER_LIB}"
    EXPORT "${STEPPER_LIB}"
    LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
    ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
    INCLUDES DESTINATION "${INC_INSTALL_DIR}/stepper"
    PUBLIC_HEADER DESTINATION "${INC_INSTALL_DIR}/stepper"
)
