add_library(valve_2_pos)

file(
    GLOB_RECURSE
    FORCE_PUMP_SOURCES
    src/*.*
)
target_compile_definitions(valve_2_pos PUBLIC HAS_HX711=0 HAS_TMC2209=0 MODBUS_ADDRESS=0x03)
target_sources(valve_2_pos PUBLIC ${FORCE_PUMP_SOURCES})

target_include_directories(valve_2_pos PUBLIC inc src/data_model)

target_link_libraries(valve_2_pos PUBLIC device stm32_bootstrap )

stm32_executable(valve_2_pos main.c)

