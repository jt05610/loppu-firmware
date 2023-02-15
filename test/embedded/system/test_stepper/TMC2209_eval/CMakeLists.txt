add_library(TMC2209Eval)

file(
    GLOB_RECURSE
    TMC2209EVAL_SOURCES
    src/*.*
)

target_sources(TMC2209Eval PUBLIC ${TMC2209EVAL_SOURCES})

target_include_directories(TMC2209Eval PUBLIC inc src/data_model)
target_compile_definitions(TMC2209Eval PUBLIC USERCONFIG)
target_link_libraries(TMC2209Eval PUBLIC device stepper)