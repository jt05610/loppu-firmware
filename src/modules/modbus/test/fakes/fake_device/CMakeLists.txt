add_library(fake_device INTERFACE)

file(
    GLOB_RECURSE
    DEVICE_SOURCES
    src/data_model/*.*
)

target_sources(fake_device INTERFACE ${DEVICE_SOURCES} src/fake_device.c)

target_include_directories(fake_device INTERFACE inc src/data_model)

target_link_libraries(fake_device INTERFACE modbus)