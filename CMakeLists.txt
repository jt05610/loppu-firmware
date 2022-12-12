cmake_minimum_required(VERSION 3.21)

set(BUTTONS_LIB buttons)
set(DATA_MODEL_LIB data_model)
set(GPIO_LIB gpio)
set(MODBUS_LIB modbus)
set(SERIAL_LIB serial)
set(STEPPER_LIB stepper)
set(TIMER_LIB timer)

set(DRIVER_INC driver_inc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)


if (${EMBEDDED})
    set(BUILD_TESTS 0)
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_VERSION 1)

    # specify cross compilers and tools for STM32
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
    set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
    set(CMAKE_AR arm-none-eabi-ar)
    set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
    set(CMAKE_OBJDUMP arm-none-eabi-objdump)
    set(SIZE arm-none-eabi-size)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

    #Uncomment for hardware floating point
    #add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
    #add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
    #add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

    #Uncomment for software floating point
    #add_compile_options(-mfloat-abi=soft)

    add_compile_options(-mcpu=cortex-m0 -mthumb -mthumb-interwork)
    add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

    project(Injector C CXX ASM)

    # uncomment to mitigate c++17 absolute addresses warnings
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")

    # Enable assembler files preprocessing
    add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        message(STATUS "Maximum optimization for speed")
        add_compile_options(-Ofast)
    elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
        message(STATUS "Maximum optimization for speed, debug info included")
        add_compile_options(-Ofast -g)
    elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
        message(STATUS "Maximum optimization for size")
        add_compile_options(-Os)
    else ()
        message(STATUS "Minimal optimization, debug info included")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
        add_compile_options(-Og -g)
    endif ()


    add_definitions(-DDEBUG -DSTM32G031xx -DUSE_FULL_LL_DRIVER)

    set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32G031F6PX_FLASH.ld)


else()
    set(BUILD_TESTS 1)
    project(Injector C CXX)
endif()

add_subdirectory(drivers)
include_directories(${DRIVER_INC})
add_subdirectory(devices)
