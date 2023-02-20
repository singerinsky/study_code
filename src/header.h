/*
 * @file:
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-11-09 09:52:42
 * @brief:
 */
#ifndef _HEADER_H_
#define _HEADER_H_
#include <gperftools/tcmalloc.h>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include "gtest/gtest.h"
#include <gperftools/profiler.h>
#include <gperftools/heap-profiler.h>
#include <features.h>
#include <map>
#include <thread>   // std::thread
#include <string>   // std::string
#include <future>   // std::promise, std::future
#include <chrono>   // seconds
#include <queue>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <type_traits>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <optional>
#include <dlfcn.h>
#include "util/asm_util.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

typedef int8_t   int8;
typedef uint8_t  uint8;
typedef int16_t  int16;
typedef uint16_t uint16;
typedef int32_t  int32;
typedef uint32_t uint32;
typedef int64_t  int64;
typedef uint64_t uint64;
using namespace std;
#endif
