set(data_model_inc_dir ${DRIVERS_ROOT_DIR}/inc/data_model)

set(
    data_model_sources
    ../../modbus/src/data_model.c
    ../../modbus/src/primary_table.c
    #api.c
)

add_library(
    "${DATA_MODEL_LIB}"
    "${DRIVERS_LIBRARY_TYPE}"
    "${data_model_sources}"
)

target_link_libraries(${DATA_MODEL_LIB} ${ST_MODBUS} ${GPIO_LIB})
