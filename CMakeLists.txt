cmake_minimum_required(VERSION 3.21)

if(${EMBEDDED})
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_VERSION 1)
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
    set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
    set(CMAKE_AR arm-none-eabi-ar)
    set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
    set(CMAKE_OBJDUMP arm-none-eabi-objdump)
    set(SIZE arm-none-eabi-size)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
endif()

project(Injector C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

macro(stm32_executable _name _main)
    set(exec ${_name}.elf)

    add_executable(${exec})

    target_sources(${exec} PUBLIC ${_main})

    target_link_libraries(${exec} PUBLIC stm32 ${_name})

    target_link_options(${exec} PUBLIC -Wl,-gc-sections,--print-memory-usage,-Map=${CMAKE_BINARY_DIR}/STM32Tests.map)

    set(HEX_FILE ${PROJECT_BINARY_DIR}/${_name}.hex)
    set(BIN_FILE ${PROJECT_BINARY_DIR}/${_name}.bin)
    add_custom_command(TARGET ${exec} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${exec}> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${exec}> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
            Building ${BIN_FILE}"
        )
endmacro()

add_subdirectory(lib)
add_subdirectory(modules)
add_subdirectory(devices)
