aux_source_directory(. LIB_SRCS)
# 添加当前目录下所有的源文件
add_library(sample SHARED ${LIB_SRCS})
# 当前目录下的文件生成一个链接库
set_target_properties(sample PROPERTIES DEBUG_POSTFIX d)