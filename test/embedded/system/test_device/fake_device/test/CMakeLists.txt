add_executable(NeedlePositionerTests)

file(
    GLOB_RECURSE
    TEST_SOURCES
    *.*
)

set(
    TEST_LIB_DEPS
    NeedlePositioner
    MockGPIO
)

target_sources(NeedlePositionerTests PUBLIC ${TEST_SOURCES})
target_include_directories(NeedlePositionerTests PRIVATE .)
target_link_libraries(NeedlePositionerTests PRIVATE NeedlePositioner MockGPIO)

gtest_discover_tests(NeedlePositionerTests)
