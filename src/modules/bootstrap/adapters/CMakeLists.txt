add_library(adapters INTERFACE)
target_include_directories(adapters INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
add_subdirectory(src/stm32)