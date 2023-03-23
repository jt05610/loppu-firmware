add_library(force_pump)

file(
    GLOB_RECURSE
    FORCE_PUMP_SOURCES
    src/*.*
)

target_sources(force_pump PUBLIC ${FORCE_PUMP_SOURCES})

target_include_directories(force_pump PUBLIC inc src/data_model)

target_link_libraries(force_pump PUBLIC device linear_axis)