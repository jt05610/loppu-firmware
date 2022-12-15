add_library(stm32_bootstrap)

file(
    GLOB_RECURSE
    SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.*
    ${CMAKE_CURRENT_SOURCE_DIR}/src/stm32/*.*
)

target_sources(stm32_bootstrap PRIVATE ${SOURCES})
target_include_directories(stm32_bootstrap PUBLIC inc src)
target_link_libraries(stm32_bootstrap PUBLIC bootstrap stm32)
if(${SIMULATED})
target_compile_definitions(stm32_bootstrap PUBLIC -DSIMULATED)
endif()
#add_subdirectory(simulator)
add_subdirectory(test)