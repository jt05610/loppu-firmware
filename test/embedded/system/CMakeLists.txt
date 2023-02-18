# ADC test

add_library(stm32_adc_test INTERFACE)
target_sources(stm32_adc_test INTERFACE test_adc/test_adc.c)
target_link_libraries(stm32_adc_test INTERFACE stm32_bootstrap)
stm32_executable(stm32_adc_test test_adc/main.c )

# Serial test

add_library(stm32_serial_test INTERFACE)
target_sources(stm32_serial_test INTERFACE test_serial/test_serial.c)
target_link_libraries(stm32_serial_test INTERFACE stm32_bootstrap unity_lib)
stm32_executable(stm32_serial_test test_serial/main.c )

# Timer test

add_library(stm32_timer_test INTERFACE)
target_sources(stm32_timer_test INTERFACE test_timer/test_timer.c)
target_include_directories(stm32_timer_test INTERFACE test_timer)
target_link_libraries(stm32_timer_test INTERFACE stm32_bootstrap unity_lib)
stm32_executable(stm32_timer_test test_timer/main.c )

# Device test

add_subdirectory(test_device/fake_device)
add_library(stm32_device_test INTERFACE)
target_sources(stm32_device_test INTERFACE test_device/test_device.c)
target_include_directories(stm32_device_test INTERFACE test_device)
target_link_libraries(stm32_device_test INTERFACE stm32_bootstrap unity_lib FakeDevice)
stm32_executable(stm32_device_test test_device/main.c)

# Stepper test

add_subdirectory(test_stepper/TMC2209_eval)
add_library(stm32_stepper_test INTERFACE)
target_sources(stm32_stepper_test INTERFACE test_stepper/test_stepper.c)
target_include_directories(stm32_stepper_test INTERFACE test_stepper)
target_link_libraries(stm32_stepper_test INTERFACE stm32_bootstrap unity_lib TMC2209Eval)
stm32_executable(stm32_stepper_test test_stepper/main.c)

add_library(stm32_linear_axis_test INTERFACE)
target_include_directories(stm32_linear_axis_test INTERFACE test_linear_axis)
target_link_libraries(stm32_linear_axis_test INTERFACE stm32_bootstrap unity_lib stepper linear_axis)
stm32_executable(stm32_linear_axis_test test_linear_axis/test_linear_axis.c)

add_library(stm32_stepdir_test INTERFACE)
target_include_directories(stm32_stepdir_test INTERFACE test_stepdir)
target_link_libraries(stm32_stepdir_test INTERFACE stm32_bootstrap unity_lib stepper)
stm32_executable(stm32_stepdir_test test_stepdir/main.c)
