cmake_minimum_required(VERSION 3.1)
project(AllCppTest)
set(CMAKE_C_COMPILER "/usr/bin/clang-12")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-12")
#set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)  #输出详细日志
#-gp 是gprof生成gmon.out,函数调用关系
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -O0 -std=c++17 -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DNDEBUG -Wl -wrap=time -pthread")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -O0 -std=c++17 -stdlib=libc++ -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DNDEBUG -Werror=return-type")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1 -std=c++17 -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DNDEBUG -Werror=return-type")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++17 -Wall -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free  -fsanitize=address  -fno-omit-frame-pointer -DNDEBUG ")


set(CMAKE_CXX_EXTENSIONS            OFF)#开关是告诉CMake采用更加通用的编译参数，比如这个开关打开，传递给GCC的参数就会是-std=c++14 而不是-std=gnu++14
#set(CMAKE_CXX_VISIBILITY_PRESET     hidden)#消除了 static 关键字上的限制更多可见性选择（4 种）来控制导出符号在代码编写阶段编写更多的代码来设置符号的可见性
#$set(CMAKE_VISIBILITY_INLINES_HIDDEN YES) # 与generate_export_header搭配使用, 设置内联函数可见性

list(APPEND CMAKE_MODULE_PATH           "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(BuildInfo)#生成构建信息
#study_cmake_build_info.h.in 是模板文件
GenerateBuildInfo(${CMAKE_CURRENT_LIST_DIR}/cmake/study_cmake_build_info.h.in ${CMAKE_CURRENT_LIST_DIR}/src/study_cmake_build_info.h)


file(GLOB_RECURSE PROTOFILE "src/cpp_proto/*.pb.*")
file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/pattern/*.cpp" "src/pattern/*.h" "src/net/*.cpp" "src/restudy/*.cpp" "src/cpu/*.cpp")

list(APPEND SRC_FILES ${PROTOFILE})
list(APPEND SRC_FILES ${UTILFILE})
file(GLOB_RECURSE SRC_HEADS "src/*.h")

find_file(exe_build NAMES AllCppTest PATHS .)
#add_custom_command(OUTPUT ${exe_log} COMMAND echo "nice")
set(WORKING_DIRECTORY "/home/ubuntu/git_space/study_code")

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
include_directories(${WORKING_DIRECTORY}/thirdparty)

find_library(gtest /usr/local/lib)
#find_library(libzmq.a ${WORKING_DIRECTORY}/libs)
find_library(liblua.a ${WORKING_DIRECTORY}/libs)
find_library(libprotobuf.a ${WORKING_DIRECTORY}/libs)
find_library(libhookstaticlib.a ${WORKING_DIRECTORY}/static_library)

SET(EXECUTABLE_OUTPUT_PATH ${WORKING_DIRECTORY}/bin) 
SET(ALL_LIBS gtest pthread glog gflags tcmalloc zmq lua dl protobuf benchmark hookstaticlib profiler)
#SET(ALL_LIBS gtest pthread glog gflags tcmalloc zmq lua dl protobuf benchmark)
add_executable(AllCppTest ${SRC_FILES} ${SRC_HEADS})
target_link_libraries(AllCppTest ${ALL_LIBS})
#target_precompile_headers(AllCppTest PUBLIC "${WORKING_DIRECTORY}/src/header.h" PRIVATE <list> <vector> <map>)
add_subdirectory(common_lib library)
add_subdirectory(common_static_lib static_library)
add_subdirectory(benchmark_one benchmark_bin)
#execute_process(COMMAND "./AllCppTest")
