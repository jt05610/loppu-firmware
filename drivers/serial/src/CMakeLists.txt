include_directories(../inc)

if (WIN32)
    set(
        serial_sources
        serial.c
        win_serial.c
    )
else ()
    set(
        serial_sources
        serial.c
        posix_serial.c
    )
endif ()

add_library(
    "${SERIAL_LIB}"
    "${serial_sources}"
)
