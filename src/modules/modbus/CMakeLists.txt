add_library(modbus INTERFACE)

file(
    GLOB_RECURSE
    MODBUS_SOURCES
    src/*.*
)

target_sources(modbus INTERFACE ${MODBUS_SOURCES})
target_include_directories(modbus INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)