add_library(NeedlePositioner)

file(
    GLOB_RECURSE
    DEVICE_SOURCES
    src/data_model/*.*
    src/needle_positioner.c
)

target_sources(NeedlePositioner PRIVATE ${DEVICE_SOURCES})

target_include_directories(NeedlePositioner PUBLIC inc PRIVATE src/data_model)

target_link_libraries(NeedlePositioner PUBLIC modbus serial gpio timer)
if(${EMBEDDED})
    stm32_executable(NeedlePositioner src/main.c)

endif()
if(${BUILD_TESTS})
    add_subdirectory(test)
endif()