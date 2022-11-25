set(data_model_inc_dir ${DRIVERS_ROOT_DIR}/inc/data_model)

set(
    data_model_sources
    discrete_inputs.c
    coils.c
    input_registers.c
    holding_registers.c
    primary_table.c
    #api.c
)

add_library(
    "${DATA_MODEL_LIB}"
    "${DRIVERS_LIBRARY_TYPE}"
    "${data_model_sources}"
)

target_link_libraries(${DATA_MODEL_LIB} ${ST_MODBUS} ${GPIO_LIB})
