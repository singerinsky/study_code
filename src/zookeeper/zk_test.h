#ifndef BA7440EB_C451_4838_A9E6_7ABD6E153026
#define BA7440EB_C451_4838_A9E6_7ABD6E153026
#include "zookeeper.h"

//初始化环境
zhandle_t* CreateNewZKHanle(const char* host);

// 初始化环境回调
void QueryServer_watcher_g(zhandle_t* zh, int type, int state,
                           const char* path, void* watcherCtx);
// 创建回调
void CreateCallBack(int rc, const char* value, const void* data);

//创建节点
void CreateNodeThread(const char* nodename);

//节点变化回调
void NodeChangeWatch(zhandle_t* zh, int type, int state, const char* path,
                     void* watcherCtx);
// 获取节点数据
void GetNodeInfo(const char* nodename);

// 获取节点
void GetNodeCallBack(int rc, const char* value, int value_len,
                     const struct Stat* stat, const void* data);


#endif /* BA7440EB_C451_4838_A9E6_7ABD6E153026 */
