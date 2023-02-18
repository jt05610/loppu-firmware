add_library(stepper INTERFACE)

file(
    GLOB_RECURSE
    STEPPER_SOURCES
    src/*.*
)

target_sources(stepper INTERFACE ${STEPPER_SOURCES})
target_include_directories(stepper INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(stepper INTERFACE tmc peripherals)
