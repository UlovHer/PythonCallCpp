cmake_minimum_required(VERSION 3.0.0)
project(TestPybind VERSION 0.1.0)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CTest)
enable_testing()
include(CPack)

# 配置Python库
# find_package(Python COMPONENTS Interpreter Development REQUIRED)
# 配置pybind11库
# find_package(pybind11 REQUIRED)
set(PYBIND11 ${PROJECT_SOURCE_DIR}/3rdparty/pybind11)
add_subdirectory(${PYBIND11})
set(Python ${PROJECT_SOURCE_DIR}/3rdparty/Python)
# find_package(Python COMPONENTS Interpreter Development)
# ${Python_INCLUDE_DIRS}
include_directories(${PYBIND11}/include ${PROJECT_SOURCE_DIR}/include ${Python}/include)
# link_directories(${Python_LIBRARY_DIRS})
link_directories(${Python}/libs)
# 配置输出
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/lib)

# 配置库后缀
set(CMAKE_DEBUG_POSTFIX "d")
# aux_source_directory(${PROJECT_SOURCE_DIR}/src/bind_func CPP_SRC)
# # 创建pybind11的模块,使用pybind11 method:
# pybind11_add_module(bind_func ${CPP_SRC})


# find_package(pybind11 CONFIG)

# # 另一种方式,使用Python method:
# Python_add_library(bind_func ${CPP_SRC})
# target_link_libraries(bind_func PUBLIC pybind11::headers)
# set_target_properties(bind_func PROPERTIES
#                                 INTERPROCEDURAL_OPTIMIZATION ON
#                                 CXX_VISIBILITY_PRESET ON
#                                 VISIBLITY_INLINES_HIDDEN ON)
# 编译为动态库
# add_library(bind_func MODULE ${CPP_SRC})
# target_link_libraries(bind_func PUBLIC pybind11::module)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/bind_func)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/bind_class)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/json_utils)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/call_python)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/embed_interpreter)
add_subdirectory(${PROJECT_SOURCE_DIR}/test/CallPython)
add_subdirectory(${PROJECT_SOURCE_DIR}/test/EmbedInterpreter)

aux_source_directory(${PROJECT_SOURCE_DIR}/src CPP_SRC)
# 编译可执行文件
add_executable(TestPybind ${CPP_SRC})
# 在C++动态库上扩展pybind11绑定
# target_link_libraries(TestPybind PUBLIC embed_interpreter)
target_link_libraries(TestPybind PUBLIC json_utils)
# define (VERSION_INFO) here.
# target_compile_definitions(bind_func PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})

