set(DATA_MODEL_DIR native)

file(
    GLOB_RECURSE
    DATA_MODEL_TEST_SRC
    ${DATA_MODEL_DIR}/*.*
)

add_library(
    ${DATA_MODEL_TEST_LIB}
    STATIC
    "${DATA_MODEL_TEST_SRC}"
    ../../gpio/test/mocks/src/mock_gpio_c.c
    ../../gpio/test/mocks/src/mock_gpio.cpp
)

include_directories(
    ${DRIVERS_ROOT_DIR}/inc/
    inc
)

target_link_libraries(
    ${DATA_MODEL_TEST_LIB}
    CppUTestExt
)
target_link_libraries(${DATA_MODEL_TEST_LIB} ${DATA_MODEL_LIB})

add_executable(DataModelTests all_tests.cpp)

target_link_libraries(
    DataModelTests
    PRIVATE
    ${DATA_MODEL_LIB}
    ${GPIO_LIB}
    ${GPIO_TEST_LIB}
    ${DATA_MODEL_TEST_LIB}
    CppUTest
    CppUTestExt
)
