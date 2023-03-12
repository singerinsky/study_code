#include "../header.h"
#include <atomic>
#include <thread>

std::atomic_bool thread_flag = ATOMIC_FLAG_INIT;


void try_to_my_lock() {
  while (thread_flag.exchange(true,std::memory_order_acquire)) {

 }
}

void try_to_unlock() {
    thread_flag.exchange(false,std::memory_order_release);
}

void exe_function() {
    while(true){
        try_to_my_lock();
        LOG(INFO) << "thread:" << std::this_thread::get_id() << " lock success! start sleep!";
        const chrono::duration sleep_time = 1s;
        std::this_thread::sleep_for(sleep_time);
        LOG(INFO) << "thread:" << std::this_thread::get_id()
                    << " unlock success! end sleep";
        try_to_unlock();
    }
}

  TEST(CasTest, test001) {
    std::thread thread_one(exe_function);  
    std::thread thread_two(exe_function);

    ::this_thread::sleep_for(100s);
}