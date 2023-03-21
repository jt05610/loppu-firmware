add_library(needle_mover)

file(
    GLOB_RECURSE
    NEEDLE_MOVER_SOURCES
    src/*.*
)

target_sources(needle_mover PUBLIC ${NEEDLE_MOVER_SOURCES})

target_include_directories(needle_mover PUBLIC inc src/data_model)

target_link_libraries(needle_mover PUBLIC device)