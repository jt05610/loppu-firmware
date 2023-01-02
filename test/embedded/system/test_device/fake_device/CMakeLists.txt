add_library(fake_device)

file(
    GLOB_RECURSE
    DEVICE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.*
)

target_sources(fake_device PUBLIC ${DEVICE_SOURCES})

target_include_directories(fake_device PUBLIC inc src/data_model)

target_link_libraries(fake_device PUBLIC device tools)
