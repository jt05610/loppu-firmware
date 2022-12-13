set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32G031F6PX_FLASH.ld)

file(
    GLOB_RECURSE
    STM32_SOURCES
    Src/*.*
    ${LINKER_SCRIPT}
    Startup/*.*
    cmsis/Device/ST/STM32G0xx/Source/*.*
)

set(
    STM32_INC_DIRS
    cmsis/Include
    Inc
    cmsis/Device/ST/STM32G0xx/Include
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    set(STM32_OPT -Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    set(STM32_OPT -Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    set(STM32_OPT -Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(STM32_OPT -Og -g)
endif ()

function(stm32_executable _name _main)
    set(exec ${_name}.elf)

    add_executable(${exec})
    set(link_options
        -Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${BLINKY_NAME}.map
        -ffunction-sections -fdata-sections -fno-common -fmessage-length=0
        -mcpu=cortex-m0 -mthumb -mthumb-interwork
        $<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>
        -T ${LINKER_SCRIPT}
        )

    target_compile_definitions(
        ${exec}
        PUBLIC
        STM32G031xx
        USE_FULL_LL_DRIVER
    )

    #target_compile_options(${exec} PRIVATE -mcpu=cortex-m0 -mthumb -mthumb-interwork)
    target_compile_options(${exec} PUBLIC -ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
    target_compile_options(${exec} PUBLIC -$<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

    target_link_options(${exec} PUBLIC -Wno-register)
    target_link_options(${exec} PUBLIC -Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${BLINKY_NAME}.map)
    target_link_options(${exec} PRIVATE -mcpu=cortex-m0 -mthumb -mthumb-interwork)
    target_link_options(${exec} PUBLIC -T ${LINKER_SCRIPT})

    set_target_properties(${exec} PROPERTIES LINK_FLAGS "/ignore:4099")

    target_compile_options(${exec} PUBLIC -mcpu=cortex-m0 -mthumb -mthumb-interwork)

    target_sources(${exec} PRIVATE ${_main} ${STM32_SOURCES})
    target_include_directories(${exec} PRIVATE ${STM32_INC_DIRS})
    add_link_options(${exec} -mcpu=cortex-m0 -mthumb -mthumb-interwork)
    add_link_options(-T ${LINKER_SCRIPT})
    target_link_options(${exec} PRIVATE ${link_options})
    target_link_libraries(${exec} PUBLIC ${_name})
    set(HEX_FILE ${PROJECT_BINARY_DIR}/${_name}.hex)
    set(BIN_FILE ${PROJECT_BINARY_DIR}/${_name}.bin)
    add_custom_command(TARGET ${exec} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${exec}> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${exec}> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
            Building ${BIN_FILE}"
        )
endfunction()
