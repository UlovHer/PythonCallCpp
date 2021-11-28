aux_source_directory(. LIB_SRC)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/test/CallPython)
# 编译可执行文件
add_executable(TestCallPython ${LIB_SRC})
# 在C++动态库上扩展pybind11绑定
target_link_libraries(TestCallPython PUBLIC call_python)



