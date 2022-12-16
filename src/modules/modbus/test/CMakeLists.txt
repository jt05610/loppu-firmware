add_executable(ModbusTests)

file(
    GLOB_RECURSE
    MODBUS_TEST_SRC
    *.*
    spies/src/*.*
)

set(
    MODBUS_TEST_INC_DIRS
    inc
    spies/inc
    ../inc
    ${CppUTest_SOURCE_DIR}/include
)

add_subdirectory(fakes/fake_device)

target_sources(ModbusTests PRIVATE ${MODBUS_TEST_SRC})

target_include_directories(ModbusTests PRIVATE ${MODBUS_TEST_INC_DIRS})

target_link_libraries(
    ModbusTests
    PRIVATE
    ${MODBUS_LIB}
    fake_device
    CppUTest
    CppUTestExt
)
