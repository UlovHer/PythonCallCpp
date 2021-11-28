aux_source_directory(. LIB_SRC)

add_library(call_python ${LIB_SRC})
# 创建pybind11的模块,使用pybind11 method:
# add_library(call_python MODULE ${LIB_SRC})
# target_link_libraries(call_python PUBLIC pybind11::module)

# define (VERSION_INFO) here.
target_compile_definitions(call_python PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})