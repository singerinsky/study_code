file(GLOB_RECURSE BENCHMARK_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)
add_executable(benchmark_one ${BENCHMARK_FILES})
target_link_libraries(benchmark_one ${ALL_LIBS})
