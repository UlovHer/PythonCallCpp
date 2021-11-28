aux_source_directory(. LIB_SRC)
pybind11_add_module(bind_class ${LIB_SRC})

# define (VERSION_INFO) here.
target_compile_definitions(bind_class PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})