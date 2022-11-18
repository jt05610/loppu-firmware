set(STEPPER_INC_DIR ${DRIVERS_ROOT_DIR}/inc/stepper)



file(
    GLOB_RECURSE
    STEPPER_SOURCES
    ${TMC_DIR}/tmc/helpers/*.*
    ${TMC_IC_DIR}/*.*
    ${TMC_DIR}/tmc/ramp/*.*
    *.c
)

include_directories(
    ${DRIVERS_ROOT_DIR}/inc
    ${TMC_DIR}
    ${TMC_IC_DIR}
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
