add_library(stm32_adapter)

file(
    GLOB_RECURSE
    SOURCES
    *.*
    src/*.*
    third_party/stm32g0xx/Src/*.*
    third_party/cmsis/Device/ST/STM32G0xx/Source/*.*
    third_party/stm32g0xx/Startup/*.*
)

set(
    INC_DIRS
    third_party/cmsis/Include
    third_party/cmsis/Device/ST/STM32G0xx/Include
    third_party/stm32g0xx/Inc
)

target_sources(stm32_adapter PUBLIC ${SOURCES})
target_compile_definitions(stm32_adapter PUBLIC -DDEBUG -DSTM32G031xx -DUSE_FULL_LL_DRIVER)
target_include_directories(stm32_adapter PUBLIC ${INC_DIRS} inc)
target_link_libraries(stm32_adapter PUBLIC adapter)