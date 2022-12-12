include_directories(
    cmsis/Device/ST/STM32G0xx/Include
    cmsis/Include
    stm32g0xx/Inc
    devices/injector/Core/Inc
    devices/injector/Core/Inc/data_model
    drivers/stModbus/include
    ${TMC_DIR}
    ${TMC_IC_DIR}
)

add_subdirectory(adapters)
add_subdirectory(injector)
add_subdirectory(pressure_sensor)
add_subdirectory(syringe_pump)
