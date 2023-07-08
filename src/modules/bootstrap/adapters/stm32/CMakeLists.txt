add_library(stm32_bootstrap)

file(
    GLOB_RECURSE
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.*
    g031xx_adapter.c
)

configure_file(config.h.in config.h @ONLY)
target_sources(stm32_bootstrap PRIVATE ${SOURCES})
target_include_directories(stm32_bootstrap PUBLIC ${CMAKE_CURRENT_LIST_DIR} PRIVATE inc src ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(stm32_bootstrap PUBLIC bootstrap stm32 tools adapters)
if(${SIMULATED})
target_compile_definitions(stm32_bootstrap PUBLIC -DSIMULATED)
endif()

add_subdirectory(test)