add_library(stm32 INTERFACE)


file(
    GLOB_RECURSE
    STM32_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.*
    ${CMAKE_CURRENT_SOURCE_DIR}/cmsis/Device/ST/STM32G0xx/*.*
)

set(
    STM32_INC_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/cmsis/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/cmsis/Device/ST/STM32G0xx/Include
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

target_sources(stm32 INTERFACE ${STM32_SOURCES})
target_include_directories(stm32 INTERFACE ${STM32_INC_DIRS})
target_compile_definitions(
    stm32
    INTERFACE
    DEBUG
    STM32G031xx
    USE_FULL_LL_DRIVER
)

target_compile_options(stm32 INTERFACE -mcpu=cortex-m0 -mthumb -mthumb-interwork)
target_compile_options(stm32 INTERFACE -ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
target_compile_options(stm32 INTERFACE $<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

target_link_options(stm32 INTERFACE -mcpu=cortex-m0 -mthumb -mthumb-interwork)

target_link_options(stm32 INTERFACE ${STM32_OPT})
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32G031F6PX_FLASH.ld)
target_link_options(stm32 INTERFACE -T ${LINKER_SCRIPT})
