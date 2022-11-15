set(BUTTONS_INC_DIR ${DRIVERS_ROOT_DIR}/inc/buttons)
set(BUTTONS_LIB buttons)
set(BUTTONS_SOURCES buttons.c)

set(
    BUTTONS_HEADERS
    ${BUTTONS_INC_DIR}/.private/buttons_private.h
    ${BUTTONS_INC_DIR}/buttons.h
)
include_directories(${GPIO_INC_DIR} ${BUTTONS_INC_DIR})

add_library(
    "${BUTTONS_LIB}"
    "${DRIVERS_LIBRARY_TYPE}"
    "${BUTTONS_HEADERS}"
    "${BUTTONS_SOURCES}"
)

target_link_libraries(${BUTTONS_LIB} ${GPIO_LIB})
