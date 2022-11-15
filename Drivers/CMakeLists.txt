set(UART_LIB "uart")
set(UART_INC_DIR ${DRIVERS_ROOT}/inc/uart)
set(DRIVER_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(DRIVER_INC)

add_subdirectory(../modules/src/uart)
add_subdirectory(../modules/test)
