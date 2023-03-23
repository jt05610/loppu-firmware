add_library(needle_mover INTERFACE)

file(
    GLOB_RECURSE
    NEEDLE_MOVER_SOURCES
    src/*.*
)

target_sources(needle_mover INTERFACE ${NEEDLE_MOVER_SOURCES})

target_include_directories(needle_mover INTERFACE inc src/data_model)

target_link_libraries(needle_mover INTERFACE device linear_axis stepper tmc)