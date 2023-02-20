add_library(linear_axis)

file(
    GLOB_RECURSE
    LINEAR_AXIS_SOURCES
    src/*.*
)

target_sources(linear_axis PUBLIC ${LINEAR_AXIS_SOURCES})
target_include_directories(linear_axis PUBLIC inc src)
target_link_libraries(linear_axis PUBLIC stepper)
