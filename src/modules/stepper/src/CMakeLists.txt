set(STEPPER_INC_DIR ${DRIVERS_ROOT_DIR}/inc/stepper)
set(TMC_DIR ../../../lib/third_party/TMC-API/tmc)
set(TMC_IC_DIR ${TMC_DIR}/ic/TMC2209)

file(
    GLOB_RECURSE
    STEPPER_SOURCES
    ${TMC_DIR}/helpers/*.*
    ${TMC_IC_DIR}/*.*
    ${TMC_DIR}/ramp/*.*
    *.c
)

include_directories(
    ${DRIVERS_ROOT_DIR}/inc
    ../../../lib/third_party/TMC-API
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
    "${STEPPER_SOURCES}"
)
