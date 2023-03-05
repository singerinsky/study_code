#include "../header.h"
#include "zookeeper.h"
#include "zk_test.h"

zhandle_t* CreateNewZKHanle(const char* host)
{
    if (host == nullptr)
    {
        assert(false);
        return nullptr;
    }
    int timeout = 30000;
    void* tmp = nullptr;
    zhandle_t* zkhandle = zookeeper_init(host, QueryServer_watcher_g, timeout, 0, tmp, 0);
    if (zkhandle == NULL)
    {
        LOG(ERROR) << "Error when connecting to zookeeper servers...\n";
        return nullptr;
    }
    return zkhandle;
}


void QueryServer_watcher_g(zhandle_t* zh, int type, int state,
                           const char* path, void* watcherCtx)
{
    if (type == ZOO_SESSION_EVENT)
    {
        if (state == ZOO_CONNECTED_STATE)
        {
            LOG(INFO) << ("[[[QueryServer]]] Connected to zookeeper service successfully!\n");
        }
        else if (state == ZOO_EXPIRED_SESSION_STATE)
        {
            LOG(INFO) << ("Zookeeper session expired!\n");
        }
        else
        {
            LOG(INFO) << " unexpected state: " << state;
        }

    }
    else
    {
        LOG(INFO) << " unexpected type: " << type;
    }
}

void CreateCallBack(int rc, const char* value, const void* data)
{
    if (rc == ZOK)
    {
        LOG(INFO) << "create node success!";
    }
    LOG(INFO) << "current thread id" << std::this_thread::get_id();
}

//创建节点
void CreateNodeThread(const char* nodename)
{
    auto zkhandle = CreateNewZKHanle("127.0.0.1:2181");
    LOG(INFO) << "do create node opertaion!";
    char buffer[512];
    strncpy(buffer, nodename, strlen(nodename));
    std::string value = std::string(nodename).append("ssss");
    int rst = zoo_acreate(zkhandle, nodename, value.c_str(), value.size(), &ZOO_OPEN_ACL_UNSAFE,
                          ZOO_EPHEMERAL, CreateCallBack, buffer);
    std::this_thread::sleep_for(5s);
    LOG(INFO) << "create result：" << rst << " and buffer is :" << buffer;
    //zookeeper_close(zhandle_t *zh)
}


void NodeChangeWatch(zhandle_t* zh, int type, int state, const char* path,
                     void* watcherCtx)
{
    LOG(INFO) << "node change!!!";
}

void GetNodeInfo(const char* nodename)
{
    std::this_thread::sleep_for(5s);
    auto zkhandle = CreateNewZKHanle("127.0.0.1:2181");
    zoo_set_watcher(zkhandle, NodeChangeWatch);
    zoo_aget(zkhandle, nodename, 1, GetNodeCallBack, NULL);
}

// 获取节点
void GetNodeCallBack(int rc, const char* value, int value_len,
                     const struct Stat* stat, const void* data)
{
    LOG(INFO) << "current thread id" << std::this_thread::get_id();
    if (rc == ZOK)
    {
        LOG(INFO) << "get call back function success,add watcher!";
    }
    else
    {
        LOG(INFO) << "get call back failed!";
    }
}

TEST(ZKTest, test_001)
{
    LOG(INFO) << "call create thread";
    CreateNodeThread("/newnode/child1");
    // auto create_thread =
    //     std::async(std::launch::async, std::bind(CreateNodeThread, "/newnode/child1"));
    // auto create_child_thread = std::async(std::launch::async, std::bind(CreateNodeThread, "/newnode/child2"));

    // auto get_thread = std::async(std::launch::async,
    //                              std::bind(GetNodeInfo, "/newnode/child1"));

    // auto get_root_thread = std::async(std::launch::async, std::bind(GetNodeInfo, "/newnode"));

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

TEST(ZKTest, test_002)
{
    LOG(INFO) << "call create thread";
    auto create_thread =
        std::async(std::launch::async, std::bind(CreateNodeThread, "/newnode/child1"));
    auto create_child_thread = std::async(std::launch::async, std::bind(CreateNodeThread, "/newnode/child2"));

    auto get_thread = std::async(std::launch::async,
                                 std::bind(GetNodeInfo, "/newnode/child1"));

    auto get_root_thread = std::async(std::launch::async, std::bind(GetNodeInfo, "/newnode"));

    constexpr auto kEndTime = 300s;
    auto kNow = std::chrono::system_clock::now();
    auto kFinishTime = std::chrono::system_clock::now() + kEndTime;
    while (kNow <= kFinishTime)
    {
        std::this_thread::sleep_until(std::chrono::system_clock::now() + 500ms);
        kNow = std::chrono::system_clock::now();
        LOG(INFO) << "Now: ";
    }
}

