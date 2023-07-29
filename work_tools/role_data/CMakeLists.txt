cmake_minimum_required(VERSION 3.1)
project(AllCppTest)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-3.8")
#set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pg -O0 -std=c++11 -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free -DNDEBUG")


file(GLOB_RECURSE SRC_FILES "src/*.cpp")
message(DEBUG  ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include/mysql++
"/usr/include/mysql")


find_library(libmysqlclient.a ${PROJECT_SOURCE_DIR}/libs/static_libs_clang_3_8)
find_library(libmysqlpp.a ${PROJECT_SOURCE_DIR}/libs/static_libs_clang_3_8)


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 
SET(ALL_LIBS pthread mysqlclient mysqlpp)
add_executable(DumpPlayer ${SRC_FILES})
target_link_libraries(DumpPlayer ${ALL_LIBS})

