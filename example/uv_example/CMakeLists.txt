file(GLOB_RECURSE BENCHMARK_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${WORKING_DIRECTORY}/bin)

find_library(libutil_lib util_lib ${WORKING_DIRECTORY}/libs)
SET(UTIL_LIB util_lib)

# include_directories(../../message_include/)
add_executable(uv_server ${BENCHMARK_FILES})
target_link_libraries(uv_server ${ALL_LIBS} ${MESSAGE_LIB} ${UTIL_LIB})
