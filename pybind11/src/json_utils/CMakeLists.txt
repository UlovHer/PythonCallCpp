aux_source_directory(. LIB_SRC)

add_library(json_utils ${LIB_SRC})

# define (VERSION_INFO) here.
target_compile_definitions(json_utils PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})