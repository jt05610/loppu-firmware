add_library(linear_axis)

file(
    GLOB_RECURSE
    LINEAR_AXIS_SOURCES
    src/*.*
)

target_sources(linear_axis PRIVATE ${LINEAR_AXIS_SOURCES})
target_include_directories(linear_axis PUBLIC inc PRIVATE src)
target_link_libraries(linear_axis stepper)
