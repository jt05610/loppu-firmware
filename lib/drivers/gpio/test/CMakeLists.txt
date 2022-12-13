add_subdirectory(fakes)
add_subdirectory(mocks)
add_executable(GPIOTests)

file(
    GLOB_RECURSE
    GPIO_TEST_SRC
    *.*
)

target_sources(GPIOTests PRIVATE ${GPIO_TEST_SRC})
target_include_directories(GPIOTests PRIVATE inc ${CppUTest_SOURCE_DIR})

target_link_libraries(
    GPIOTests
    PRIVATE
    FakeGPIO
    MockGPIO
    CppUTest
)
