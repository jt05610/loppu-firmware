add_library(adc INTERFACE)
target_sources(adc INTERFACE src/analog.c)
target_include_directories(adc INTERFACE inc)