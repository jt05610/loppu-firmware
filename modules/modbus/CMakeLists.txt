add_library(modbus)

file(
    GLOB_RECURSE
    MODBUS_SOURCES
    src/*.*
)

target_sources(modbus PRIVATE ${MODBUS_SOURCES})
target_include_directories(modbus PUBLIC inc/public PRIVATE inc/.private)