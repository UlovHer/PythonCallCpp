aux_source_directory(. LIB_SRC)

add_library(embed_interpreter ${LIB_SRC})
# 创建pybind11的模块,使用pybind11 method:
# add_library(embed_interpreter MODULE ${LIB_SRC})
# target_link_libraries(embed_interpreter PUBLIC pybind11::module)

# define (VERSION_INFO) here.
target_compile_definitions(embed_interpreter PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})