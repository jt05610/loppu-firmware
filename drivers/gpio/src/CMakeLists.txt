set(GPIO_INC_DIR ${DRIVERS_ROOT_DIR}/inc/gpio)
set(GPIO_LIB gpio)
set(GPIO_SOURCES gpio.c)
include_directories(../inc)
add_library(
    "${GPIO_LIB}"
    "${DRIVERS_LIBRARY_TYPE}"
    "${GPIO_HEADERS}"
    "${GPIO_SOURCES}"
)
