cmake_minimum_required(VERSION 3.26)

set(CMAKE_C_COMPILER "/usr/bin/clang-15")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-15")
project(AllCppTest)

# set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON) # 输出详细日志

# -gp 是gprof生成gmon.out,函数调用关系
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -O0 -std=c++17 -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DNDEBUG -Wl -wrap=time -pthread")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -O0 -std=c++17 -stdlib=libc++ -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DNDEBUG -Werror=return-type")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++17 -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DNDEBUG -Werror=return-type")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -DNDEBUG ")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++17 -Wall -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free  -fsanitize=address  -fno-omit-frame-pointer -DNDEBUG ")

# cmake 合并编译
SET(CMAKE_UNITY_BUILD ON)
set(CMAKE_UNITY_BUILD_BATCH_SIZE 5)
set(WORKING_DIRECTORY "/home/gl/workspace/study_code")
add_definitions(-DTHREADED)
set(CMAKE_CXX_EXTENSIONS OFF) # 开关是告诉CMake采用更加通用的编译参数，比如这个开关打开，传递给GCC的参数就会是-std=c++14 而不是-std=gnu++14

# set(CMAKE_CXX_VISIBILITY_PRESET     hidden)#消除了 static 关键字上的限制更多可见性选择（4 种）来控制导出符号在代码编写阶段编写更多的代码来设置符号的可见性
# $set(CMAKE_VISIBILITY_INLINES_HIDDEN YES) # 与generate_export_header搭配使用, 设置内联函数可见性
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(BuildInfo) # 生成构建信息

# study_cmake_build_info.h.in 是模板文件
GenerateBuildInfo(${CMAKE_CURRENT_LIST_DIR}/cmake/study_cmake_build_info.h.in ${CMAKE_CURRENT_LIST_DIR}/src/study_cmake_build_info.h)

file(GLOB_RECURSE PROTOFILE "src/cpp_proto/*.pb.*")
file(GLOB_RECURSE SRC_FILES "src/*.cpp") # "src/pattern/*.cpp" "src/pattern/*.h" "src/net/*.cpp" "src/restudy/*.cpp" "src/cpu/*.cpp" "src/zookeeper/*.cpp" "src/rapidjson/*.cpp" "src/uv_test/*.cpp" )

# aux_source_directory("src" SRC_FILES)
list(APPEND SRC_FILES ${PROTOFILE})
list(APPEND SRC_FILES ${UTILFILE})
file(GLOB_RECURSE SRC_HEADS "src/*.h")

find_file(exe_build NAMES AllCppTest PATHS .)

# add_custom_command(OUTPUT ${exe_log} COMMAND echo "nice")
# 绝对路径
macro(use_precompiled_header TARGET HEADER_FILE SRC_FILE)
  get_filename_component(HEADER ${HEADER_FILE} NAME)

  # Use MSVC_IDE to exclude NMake from using PCHs
  if(MSVC AND NOT NMAKE AND NOT OGRE_UNITY_BUILD)
    set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS /Yu"${HEADER}")
    set_source_files_properties(${SRC_FILE}
      PPROPERTIES COMPILE_FLAGS /Yc"${HEADER}"
    )
  elseif(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX)
  endif()
endmacro(use_precompiled_header)

include_directories(${WORKING_DIRECTORY}/src/include
  ${WORKING_DIRECTORY}/src/include/lua
  ${WORKING_DIRECTORY}/src/include/zookeeper
  ${WORKING_DIRECTORY}/thirdparty
  ${WORKING_DIRECTORY}/message_include
)

# link_directories(${WORKING_DIRECTORY}/lib_bak /usr/local/lib)
find_library(gtest /usr/local/lib)
find_library(libzookeeper zookeeper ${WORKING_DIRECTORY}/libs)
find_library(libhashtable hashtable ${WORKING_DIRECTORY}/libs)
find_library(libuv uv ${WORKING_DIRECTORY}/libs)
find_library(liblua lua ${WORKING_DIRECTORY}/libs)
find_library(libmysqlclient mysqlclient ${WORKING_DIRECTORY}/libs)
find_library(libprotobuf protobuf ${WORKING_DIRECTORY}/libs})

file(GLOB PROTO_SOURCES ${WORKING_DIRECTORY}/src/protofile/*.proto)
execute_process(COMMAND sh ${WORKING_DIRECTORY}/src/protofile/gen.sh ${WORKING_DIRECTORY} ${PROTO_SOURCES})

# message("${WORKING_DIRECTORY}")
add_custom_target(protobuild COMMAND sh ${WORKING_DIRECTORY}/src/protofile/gen.sh ${WORKING_DIRECTORY} ${PROTO_SOURCES})

# target_precompile_headers(AllCppTest PUBLIC "${WORKING_DIRECTORY}/src/header.h" PRIVATE <list> <vector> <map>)
add_subdirectory(common_lib library)
add_subdirectory(common_static_lib static_library)
add_subdirectory(src/cpp_proto messagelib)

find_library(libmessagelib messagelib ${WORKING_DIRECTORY}/libs)

link_directories(${WORKING_DIRECTORY}/library)

SET(MESSAGE_LIB messagelib)

SET(EXECUTABLE_OUTPUT_PATH ${WORKING_DIRECTORY}/bin)
SET(ALL_LIBS gtest pthread gflags glog tcmalloc zmq ${liblua} dl ${libprotobuf} benchmark hookstaticlib profiler ${libzookeeper} ${libhashtable} ${libuv} crypto ssl numa ${libmysqlclient} libluatestlib.so)

# 

add_subdirectory(src)

# add_subdirectory(benchmark_one)

# add_subdirectory(example/util)
# add_subdirectory(example/uv_example)
# add_subdirectory(example/tcp_client)
execute_process(COMMAND "./AllCppTest")
