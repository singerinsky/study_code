
/*
 * @file:
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-10-31 17:23:01
 * @brief:
 */

#ifndef D55716AB_EE5D_4C67_9570_8B653FF3358B
#define D55716AB_EE5D_4C67_9570_8B653FF3358B

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

template <typename T> class ThreadSafeQueue {
private:
  std::queue<T> data_queue; // 存储数据的队列
  mutable std::mutex mut;   // 互斥锁，用于保护数据队列的访问
  std::condition_variable data_cond; // 条件变量，用于线程间的同步

public:
  ThreadSafeQueue() {} // 构造函数

  void push(T data) {
    std::lock_guard<std::mutex> lk(
        mut); // 创建一个独占的互斥锁，并将其与互斥量mut关联
    data_queue.push(std::move(data)); // 将数据移动到队列中
    data_cond.notify_one(); // 通知一个等待在条件变量data_cond上的线程
  }

  std::shared_ptr<T> waitAndPop() {
    std::unique_lock<std::mutex> lk(
        mut); // 创建一个独占的互斥锁，并将其与互斥量mut关联

    // 等待条件变量data_cond满足条件，即data_queue非空
    // 如果条件不满足，当前线程会释放互斥锁，并阻塞等待
    data_cond.wait(lk, [this] { return !data_queue.empty(); });

    std::shared_ptr<T> res = std::make_shared<T>(std::move(
        data_queue
            .front())); // 创建一个shared_ptr对象res，通过移动语义获取队列头部元素的所有权
    data_queue.pop();   // 弹出队列头部元素
    return res; // 返回shared_ptr对象res，即弹出的队列头部元素
  }

  std::shared_ptr<T> tryPop() {
    std::lock_guard<std::mutex> lk(
        mut); // 创建一个独占的互斥锁，并将其与互斥量mut关联

    if (data_queue.empty())
      return nullptr; // 如果队列为空，返回空指针

    std::shared_ptr<T> res = std::make_shared<T>(std::move(
        data_queue
            .front())); // 创建一个shared_ptr对象res，通过移动语义获取队列头部元素的所有权
    data_queue.pop();   // 弹出队列头部元素
    return res; // 返回shared_ptr对象res，即弹出的队列头部元素
  }

  bool empty() const {
    std::lock_guard<std::mutex> lk(
        mut); // 创建一个独占的互斥锁，并将其与互斥量mut关联
    return data_queue.empty(); // 返回队列是否为空
  }
};

#endif /* D55716AB_EE5D_4C67_9570_8B653FF3358B */
