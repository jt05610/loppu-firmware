add_library(adapter)
target_sources(adapter PRIVATE src/adapter.c)
target_include_directories(adapter PUBLIC inc)
target_link_libraries(adapter PUBLIC gpio serial timer)