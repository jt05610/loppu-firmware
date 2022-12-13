cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

if(${EMBEDDED})

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

    project(Injector C CXX ASM)
    #Uncomment for hardware floating point
    #add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
    #add_compile_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)
    #add_link_options(-mfloat-abi=hard -mfpu=fpv4-sp-d16)

    #Uncomment for software floating point
    #add_compile_options(-mfloat-abi=soft)


else()
    set(${BUILD_TESTS} 1)
    project(Injector C CXX)
endif()


add_subdirectory(lib)

add_subdirectory(modules)
add_subdirectory(devices)
