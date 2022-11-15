set(
    SERIAL_TEST_HEADERS
    fakes/inc/fake_serial.h
    spies/inc/serial_spy.h
)

if (WIN32)
    set(
        SERIAL_TEST_SRC
        serial_test.cpp
        serial_spy_test.cpp
        win_serial_test.cpp
        fakes/src/fake_serial.c
        spies/src/serial_spy.c
    )
else ()
    set(
        SERIAL_TEST_SRC
        serial_test.cpp
        serial_spy_test.cpp
        posix_serial_test.cpp
        fakes/src/fake_serial.c
        spies/src/serial_spy.c
    )
endif ()

add_library(
    "${SERIAL_TEST_LIB}"
    "${SERIAL_TEST_HEADERS}"
    "${SERIAL_TEST_SRC}"
)

include_directories(
    fakes/inc
    spies/inc
    ${DRIVERS_ROOT_DIR}/inc/
)

target_link_libraries(${SERIAL_TEST_LIB} ${SERIAL_LIB})

add_executable(SerialTests all_tests.cpp)

target_link_libraries(
    SerialTests
    PRIVATE
    ${DRIVER_TEST_LIBS}
    CppUTest
    CppUTestExt
)
