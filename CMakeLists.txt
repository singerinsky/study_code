cmake_minimum_required(VERSION 3.1)
project(AllCppTest)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-7")
#set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -O0 -std=c++17 -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DNDEBUG")

file(GLOB_RECURSE PROTOFILE "src/cpp_proto/*.pb.*")
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/pattern/*.cpp" "src/pattern/*.h")

list(APPEND SRC_FILES ${PROTOFILE})
list(APPEND SRC_FILES ${UTILFILE})
file(GLOB_RECURSE SRC_HEADS "src/*.h")

find_file(exe_build NAMES AllCppTest PATHS .)
#add_custom_command(OUTPUT ${exe_log} COMMAND echo "nice")
set(WORKING_DIRECTORY "/home/ubuntu/study_space")

macro(use_precompiled_header TARGET HEADER_FILE SRC_FILE)
  get_filename_component(HEADER ${HEADER_FILE} NAME)
  # Use MSVC_IDE to exclude NMake from using PCHs
  if (MSVC AND NOT NMAKE AND NOT OGRE_UNITY_BUILD)
    set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS /Yu"${HEADER}")
    set_source_files_properties(${SRC_FILE}
      PPROPERTIES COMPILE_FLAGS /Yc"${HEADER}"
    )
  elseif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
  endif ()
endmacro(use_precompiled_header)



include_directories(${WORKING_DIRECTORY}/src/include)
include_directories(${WORKING_DIRECTORY}/src/cpp_proto)
include_directories(${WORKING_DIRECTORY}/src/include/lua)

find_library(gtest /usr/local/lib)
find_library(libzmq.a ${WORKING_DIRECTORY}/libs)
find_library(liblua.a ${WORKING_DIRECTORY}/libs)
find_library(libprotobuf.a ${WORKING_DIRECTORY}/libs)

SET(EXECUTABLE_OUTPUT_PATH ${WORKING_DIRECTORY}) 
SET(ALL_LIBS gtest pthread glog gflags tcmalloc zmq lua dl protobuf benchmark)
add_executable(AllCppTest ${SRC_FILES} ${SRC_HEADS})
target_link_libraries(AllCppTest ${ALL_LIBS})
#target_precompile_headers(AllCppTest PUBLIC "${WORKING_DIRECTORY}/src/header.h" PRIVATE <list> <vector> <map>)
add_subdirectory(common_lib library)
add_subdirectory(benchmark_one benchmark_bin)
#execute_process(COMMAND "./AllCppTest")
#test for pick
