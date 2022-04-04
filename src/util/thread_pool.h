/*
 * @file: 
 * @copyright: 2012 - 2028 ByteDance. All Rights Reserved
 * @Author: guanlei
 * @Date: 2021-10-31 17:23:01
 * @brief: 
 */

#include <iostream>
#include <thread>
#include <queue>

template<typename T>
class ThreadSafeQueue {
private:
  std::queue<T> data_queue;
  mutable std::mutex mut;
  std::condition_variable data_cond;
public:
  ThreadSafeQueue() {}
  void push(T data) {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(std::move(data));
    data_cond.notify_one();
  }
   
  std::shared_ptr<T> waitAndPop() {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk,[this]{
      return !data_queue.empty();
    });
    std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
    data_queue.pop();
    return res;
  }
   
  std::shared_ptr<T> tryPop() {
    std::lock_guard<std::mutex> lk(mut);
    if(data_queue.empty())
      return nullptr;
    std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
    data_queue.pop();
    return res;
  }
   
  bool empty() const {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};