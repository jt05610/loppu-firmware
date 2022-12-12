add_library(fake_device)

file(
    GLOB_RECURSE
    DEVICE_SOURCES
    src/data_model/*.*
)

target_sources(fake_device PRIVATE ${DEVICE_SOURCES} PUBLIC src/fake_device.c)

target_include_directories(fake_device PUBLIC inc PRIVATE src/data_model)

target_link_libraries(fake_device PRIVATE ${MODBUS_LIB})