add_library(serial INTERFACE)
target_sources(serial INTERFACE src/serial.c)
target_include_directories(serial INTERFACE inc tools)
add_subdirectory(test)