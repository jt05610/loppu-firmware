add_library(stm32_serial_tests INTERFACE)

file(
    GLOB_RECURSE
    SOURCES
    test_*.*
)

target_sources(stm32_serial_tests INTERFACE ${SOURCES})
target_include_directories(stm32_serial_tests INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(stm32_serial_tests INTERFACE stm32_bootstrap unity_lib FakeDevice)
stm32_executable(stm32_serial_tests main.c)

