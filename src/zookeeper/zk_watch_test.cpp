#include "../header.h"
#include "zookeeper.h"
#include "zk_test.h"
#include <future>


TEST(ZKTest, test_watcher_001)
{
    LOG(INFO) << "call create thread";
    CreateNodeThread("/newnode/child1");

    auto get_call_back = []()
    {
        std::this_thread::sleep_for(6s);
        auto zkhandle = CreateNewZKHanle("127.0.0.1:2181");
        LOG(INFO) << " start awget....";
        int rst = zoo_awget(
                      zkhandle, "/newnode/child1",
                      [](zhandle_t* zh, int type, int state, const char* path,
                         void* watcherCtx)
        {
            LOG(INFO) << "while node change";
        },
        nullptr,
        [](int rc, const char* value, int value_len,
           const struct Stat * stat, const void* data)
        {
            LOG(INFO) << " while node get data " << rc;
        }, NULL);
    };

    auto call_rst = std::async(std::launch::async, get_call_back);

    const constexpr auto kEndTime = 300s;
    auto kNow = std::chrono::system_clock::now();
    auto kFinishTime = std::chrono::system_clock::now() + kEndTime;
    while (kNow <= kFinishTime)
    {
        std::this_thread::sleep_until(std::chrono::system_clock::now() + 500ms);
        kNow = std::chrono::system_clock::now();
        LOG(INFO) << "Now: ";
    }
}

