add_library(mocks INTERFACE)

macro(create_mock _name)
    set(_lib mock_${_name})
    add_library(${_lib})
    target_sources(${_lib} PRIVATE Mock${_name}.c)
    target_include_directories(${_lib} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${_lib} PUBLIC ${_name} cmock unity)
endmacro()

create_mock(serial)
create_mock(gpio)
create_mock(timer)
target_link_libraries(mocks INTERFACE serial_mock gpio_mock timer_mock)
