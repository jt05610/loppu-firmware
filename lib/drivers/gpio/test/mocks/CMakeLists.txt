add_library(MockGPIO)

target_sources(MockGPIO PRIVATE src/mock_gpio_c.c src/mock_gpio.cpp)

target_include_directories(MockGPIO PUBLIC inc ${CppUTest_SOURCE_DIR}/include)

target_link_libraries(MockGPIO PRIVATE gpio CppUTestExt)
