add_library(${MODBUS_LIB})

file(
    GLOB_RECURSE
    MODBUS_SOURCES
    src/*.*
)

target_sources(${MODBUS_LIB} PRIVATE ${MODBUS_SOURCES})
target_include_directories(${MODBUS_LIB} PUBLIC inc/public PRIVATE inc/.private)
