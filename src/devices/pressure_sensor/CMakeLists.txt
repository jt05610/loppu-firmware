add_library(PressureSensor)

file(
    GLOB_RECURSE
    PRESSURESENSOR_SOURCES
    src/*.*
)

target_sources(PressureSensor PUBLIC ${PRESSURESENSOR_SOURCES})

target_include_directories(PressureSensor PUBLIC inc src/data_model)

target_link_libraries(PressureSensor PUBLIC device stm32_bootstrap)

stm32_executable(PressureSensor src/main.c)

