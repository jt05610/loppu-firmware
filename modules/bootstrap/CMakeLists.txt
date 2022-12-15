add_library(bootstrap INTERFACE)
target_sources(bootstrap INTERFACE src/bootstrap.c)
target_include_directories(bootstrap INTERFACE inc)
target_link_libraries(bootstrap INTERFACE peripherals)

add_subdirectory(adapters/stm32)
