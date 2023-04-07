file(GLOB_RECURSE BENCHMARK_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${WORKING_DIRECTORY}/bin)

find_library(libutil_lib util_lib ${WORKING_DIRECTORY}/libs)
SET(UTIL_LIB util_lib)
add_executable(uv_client ${BENCHMARK_FILES})
target_link_libraries(uv_client ${ALL_LIBS} ${MESSAGE_LIB} ${UTIL_LIB})
