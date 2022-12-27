add_library(device INTERFACE)
target_sources(device INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/device.c)
target_include_directories(device INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(device INTERFACE modbus peripherals)