set(GPIO_INC_DIR ${DRIVERS_ROOT_DIR}/inc/gpio)
set(GPIO_LIB gpio)
set(GPIO_SOURCES gpio.c)

set(
    GPIO_HEADERS
    ${GPIO_INC_DIR}/.private/gpio_private.h
    ${GPIO_INC_DIR}/gpio.h
)
add_library(
    "${GPIO_LIB}"
    "${DRIVERS_LIBRARY_TYPE}"
    "${GPIO_HEADERS}"
    "${GPIO_SOURCES}"
)

target_include_directories(
    ${GPIO_LIB}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../inc>
    $<INSTALL_INTERFACE:inc>
)


set_target_properties(
    "${GPIO_LIB}" PROPERTIES
    PUBLIC_HEADER "${GPIO_HEADERS}"
)

install(
    TARGETS "${GPIO_LIB}"
    EXPORT "${GPIO_LIB}"
    LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
    ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
    INCLUDES DESTINATION "${INC_INSTALL_DIR}/gpio"
    PUBLIC_HEADER DESTINATION "${INC_INSTALL_DIR}/gpio"
)
