add_library(serial src/serial.c)
target_include_directories(serial PUBLIC inc)
add_subdirectory(test)