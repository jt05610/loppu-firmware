add_library(force_pump INTERFACE)

file(
    GLOB_RECURSE
    FORCE_PUMP_SOURCES
    src/*.*
)

target_sources(force_pump INTERFACE ${FORCE_PUMP_SOURCES})

target_include_directories(force_pump INTERFACE inc src/data_model)

target_link_libraries(force_pump INTERFACE device linear_axis stepper tmc hx711)