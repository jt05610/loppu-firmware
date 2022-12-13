include(FetchContent)

if (${EMBEDDED})
    # STM32
    add_subdirectory(stm32g0xx)
else()
    # GoogleTest

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
    enable_testing()
    include(GoogleTest)

    function(create_test)
    endfunction()

    # CppUTest

    fetchcontent_declare(
        CppUTest
        GIT_REPOSITORY https://github.com/cpputest/cpputest.git
        GIT_TAG latest-passing-build
    )

    set(TESTS OFF CACHE BOOL "Switch off CPPUTest Test build")
    fetchcontent_makeavailable(CppUTest)

endif()

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.5.2
)

FetchContent_MakeAvailable(unity)

add_library(cmock CMock/src/cmock.c)
target_include_directories(cmock PUBLIC CMock/src ${unity_SOURCE_DIR}/src)


# TMC-API

set(TMC_IC TMC2209)
set(TMC_IC_PATH TMC-API/tmc/ic/${TMC_IC})

add_library(tmc)
file(
    GLOB_RECURSE
    TMC_SOURCES
    TMC-API/tmc/helpers/*.*
    TMC-API/tmc/ramp/*.*
    ${TMC_IC}*.*
)

target_sources(tmc PRIVATE ${TMC_SOURCES})
target_include_directories(tmc PUBLIC TMC-API ${TMC_IC_PATH})