add_library(FakeGPIO)
target_sources(FakeGPIO PRIVATE src/fake_gpio.c)
target_include_directories(FakeGPIO PUBLIC inc)
target_link_libraries(FakeGPIO PRIVATE gpio)
