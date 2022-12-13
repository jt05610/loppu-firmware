add_library(gpio)
target_sources(gpio PRIVATE src/gpio.c)
target_include_directories(gpio PUBLIC inc)
add_subdirectory(mocks)
