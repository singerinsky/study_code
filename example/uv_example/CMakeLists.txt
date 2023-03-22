file(GLOB_RECURSE BENCHMARK_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${WORKING_DIRECTORY}/bin)
add_executable(uv_server ${BENCHMARK_FILES})
target_link_libraries(uv_server ${ALL_LIBS})
