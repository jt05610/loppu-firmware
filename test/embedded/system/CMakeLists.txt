# ADC test

add_library(stm32_adc_test INTERFACE)
target_sources(stm32_adc_test INTERFACE test_adc/test_adc.c)
target_link_libraries(stm32_adc_test INTERFACE stm32_bootstrap)
stm32_executable(stm32_adc_test test_adc/main.c )

# Serial test

add_library(stm32_serial_test INTERFACE)
target_sources(stm32_serial_test INTERFACE test_serial/test_serial.c)
target_link_libraries(stm32_serial_test INTERFACE stm32_bootstrap)
stm32_executable(stm32_serial_test test_serial/main.c )

# Timer test

add_library(stm32_timer_test INTERFACE)
target_sources(stm32_timer_test INTERFACE test_timer/test_timer.c)
target_include_directories(stm32_timer_test INTERFACE test_timer)
target_link_libraries(stm32_timer_test INTERFACE stm32_bootstrap unity_lib)
stm32_executable(stm32_timer_test test_timer/main.c )
