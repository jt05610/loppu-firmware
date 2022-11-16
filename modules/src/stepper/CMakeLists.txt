set(STEPPER_INC_DIR ${DRIVERS_ROOT_DIR}/inc/stepper)

file(
    GLOB_RECURSE
    STEPPER_SOURCES
    *.c
)

include_directories(
    ${DRIVERS_ROOT_DIR}/inc
)
set(
    STEPPER_HEADERS
    ${STEPPER_INC_DIR}/.private/stepper_private.h
    ${STEPPER_INC_DIR}/stepper_driver.h
)

add_library(
    "${STEPPER_LIB}"
    "${DRIVERS_LIBRARY_TYPE}"
    "${STEPPER_HEADERS}"
    "${STEPPER_SOURCES}"
)
