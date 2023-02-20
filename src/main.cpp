#include "header.h"
#include "study_cmake_build_info.h"
#include "lua_case/lua_test_one.h"
#include "lua_case/test_lua_bridge.h"
#include "mmap_case/test_mmap.h"
#include "stl_case/set.hpp"
#include "stl_case/test_template_stl.h"
#include "test_case/test_array.h"
#include "test_case/test_atom.h"
#include "test_case/test_brk.h"
#include "test_case/test_daemon.h"
#include "test_case/test_epoll.h"
#include "test_case/test_foreach.h"
#include "test_case/test_hash.h"
#include "test_case/test_new.h"
#include "test_case/test_queue.h"
#include "test_case/test_shm.h"
#include "test_case/test_sort.h"
#include "test_case/test_static.h"
#include "test_case/test_tcmalloc.h"
#include "test_case/test_thread_safe.h"
#include "util/res_guard.h"
#include "util/test_move.h"
#include "lua_case/lua_pure.h"
#include "pattern/pattern_visitor.h"
#include "cpu/cpu_test.h"

int main(int argc, char** argv)
{

    testing::InitGoogleTest(&argc, argv);
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    // 初始化日志库
    google::InitGoogleLogging(argv[0]);
    FLAGS_logtostderr = true;
    LOG(INFO) << "Current running time build is " << StudyCmakeBuildInfo::Timestamp << endl;
    LOG(ERROR) << "Start All Test!";

    //ProfilerStart("study.prof");
    HeapProfilerStart("heap/study");
    int test_rst = RUN_ALL_TESTS();
    HeapProfilerStop();
    //ProfilerStop();
    return 1;
}
