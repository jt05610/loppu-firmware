set(serial_inc_dir ${DRIVERS_ROOT_DIR}/inc/serial)

if (WIN32)
    set(
        serial_sources
        serial.c
        win_serial.c
    )
    set(serial_headers
        ${serial_inc_dir}/.private/serial_private.h
        ${serial_inc_dir}/serial.h
        ${serial_inc_dir}/win_serial.h
        ${DRIVERS_ROOT_DIR}/../inc/project_types.h
        )
else ()
    set(
        serial_sources
        serial.c
        posix_serial.c
    )
    set(serial_headers
        ${serial_inc_dir}/.private/serial_private.h
        ${serial_inc_dir}/posix_serial.h
        )
endif ()

add_library(
    "${SERIAL_LIB}"
    "${DRIVERS_LIBRARY_TYPE}"
    "${serial_headers}"
    "${serial_sources}"
)

target_include_directories(
    ${SERIAL_LIB}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../inc>
    $<INSTALL_INTERFACE:inc>
)

set_target_properties(
    "${SERIAL_LIB}" PROPERTIES
    PUBLIC_HEADER "${serial_headers}"
)

install(
    TARGETS "${SERIAL_LIB}"
    EXPORT "${SERIAL_LIB}"
    LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
    ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
    INCLUDES DESTINATION "${INC_INSTALL_DIR}/serial"
    PUBLIC_HEADER DESTINATION "${INC_INSTALL_DIR}/serial"
)
