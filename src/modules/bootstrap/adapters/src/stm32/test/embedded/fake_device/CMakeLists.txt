add_library(FakeDevice)

file(
    GLOB_RECURSE
    FAKEDEVICE_SOURCES
    src/*.*
)

target_sources(FakeDevice PUBLIC ${FAKEDEVICE_SOURCES})

target_include_directories(FakeDevice PUBLIC inc PUBLIC src/data_model)

target_link_libraries(FakeDevice PUBLIC modbus peripherals)