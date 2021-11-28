aux_source_directory(. LIB_SRC)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/test/EmbedInterpreter)
# 编译可执行文件
add_executable(TestEmbedInterpreter ${LIB_SRC})
# 在C++动态库上扩展pybind11绑定
target_link_libraries(TestEmbedInterpreter PUBLIC embed_interpreter)



