add_library(hx711 INTERFACE)

file(
    GLOB_RECURSE
    LINEAR_AXIS_SOURCES
    *.*
)

target_sources(hx711 INTERFACE ${LINEAR_AXIS_SOURCES})
target_include_directories(hx711 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(hx711 INTERFACE spi)