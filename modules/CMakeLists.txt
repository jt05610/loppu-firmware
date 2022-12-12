

file(
    GLOB_RECURSE
    DRIVER_SOURCE
    "${DRIVERS_ROOT_DIR}/src/*.*"
)

include_directories(../drivers/stModbus/include)
set(
    st_modbus_src
    ../drivers/stModbus/src/rtu/mbutils.c
    ../drivers/stModbus/src/modbus.c
)

add_library(ST_MODBUS STATIC ${st_modbus_src})

include_directories(inc)
add_subdirectory(src/serial)
add_subdirectory(src/gpio)
add_subdirectory(src/timer)
add_subdirectory(src/stepper)
add_subdirectory(src/buttons)
add_subdirectory(src/data_model)
add_subdirectory(test)
