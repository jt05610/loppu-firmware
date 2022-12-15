if ((${EMBEDDED}))
    set(${TEST_LIB} unity_lib)
    macro(create_unity_test)

    endmacro()
    set(create_test create_unity_test)
else()
    # GoogleTest

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

endif()

macro(create_test _name _runner _deps)
   if(${EMBEDDED})

   else()
       set(_exec ${_name})
       add_executable(${_exec})
       target_sources(${_exec} PRIVATE ${_runner})
       target_link_libraries(${_exec} PRIVATE GTest::gtest_main ${_deps})
       gtest_discover_tests(${_exec})
   endif()
endmacro()
enable_testing()

add_subdirectory(lib)
