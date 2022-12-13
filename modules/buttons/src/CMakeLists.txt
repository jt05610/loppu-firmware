set(BUTTONS_INC_DIR ${DRIVERS_ROOT_DIR}/inc/buttons)
set(BUTTONS_LIB buttons)
set(BUTTONS_SOURCES buttons.c)

add_library(
    "${BUTTONS_LIB}"
    "${BUTTONS_SOURCES}"
)

target_link_libraries(${BUTTONS_LIB} ${GPIO_LIB})
