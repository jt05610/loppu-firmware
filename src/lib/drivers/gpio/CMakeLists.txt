add_library(gpio INTERFACE)
target_sources(gpio INTERFACE src/gpio.c)
target_include_directories(gpio INTERFACE inc)
add_subdirectory(mocks)
