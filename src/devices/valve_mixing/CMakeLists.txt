add_library(valve_mixing)

file(
    GLOB_RECURSE
    FORCE_PUMP_SOURCES
    src/*.*
)
target_compile_definitions(valve_mixing PUBLIC HAS_HX711=1 HAS_TMC2209=1 MODBUS_ADDRESS=0x02)
target_sources(valve_mixing PUBLIC ${FORCE_PUMP_SOURCES})

target_include_directories(valve_mixing PUBLIC inc src/data_model)

target_link_libraries(valve_mixing PUBLIC device linear_axis stepper tmc hx711 stm32_bootstrap )

stm32_executable(valve_mixing main.c)

