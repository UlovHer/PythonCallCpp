aux_source_directory(. LIB_SRC)
# 创建pybind11的模块,使用pybind11 method:
pybind11_add_module(bind_func ${LIB_SRC})

# define (VERSION_INFO) here.
target_compile_definitions(bind_func PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})