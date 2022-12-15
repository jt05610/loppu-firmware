add_library(peripherals INTERFACE)
target_include_directories(peripherals INTERFACE src)
target_link_libraries(peripherals INTERFACE serial gpio timer)
