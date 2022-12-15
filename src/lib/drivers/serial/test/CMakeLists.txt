
file(
    GLOB_RECURSE
    SERIAL_SOURCES
    *.*
)

add_executable(SerialTests ${SERIAL_SOURCES})

target_link_libraries(SerialTests PUBLIC unity serial)
