set(DEVICE_NAME syringe_pump)
file(
    GLOB_RECURSE
    DEVICE_SOURCES
    "Core/*.*"
)

set(
    DEVICE_LIBS
    ${BUTTONS_LIB}
    ${DATA_MODEL_LIB}
    ${GPIO_LIB}
    ${MODBUS_LIB}
    ${SERIAL_LIB}
    ${STEPPER_LIB}
    ${TIMER_LIB}
)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${DEVICE_NAME}.map)
add_link_options(-mcpu=cortex-m0 -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})
add_executable(${DEVICE_NAME}.elf ${DEVICE_SOURCES} ${LINKER_SCRIPT})
target_link_libraries(${DEVICE_NAME}.elf ${DEVICE_LIBS})
set(HEX_FILE ${PROJECT_BINARY_DIR}/${DEVICE_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${DEVICE_NAME}.bin)

add_custom_command(TARGET ${DEVICE_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${DEVICE_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${DEVICE_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${HEX_FILE}
        Building ${BIN_FILE}"
    )

