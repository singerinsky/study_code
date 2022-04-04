#pragma once
#include "../header.h"
#include "../util/concurrentqueue.h"
#include "../util/class_sample.h"

TEST(Test_Queue,test1)
{
    moodycamel::ConcurrentQueue<int> q;
    int items[] = { 1, 2, 3, 4, 5 };
    q.enqueue_bulk(items, 5);
    

    int results[5];     // Could also be any iterator
    size_t count = q.try_dequeue_bulk(results, 5);
    for (size_t i = 0; i != count; ++i) {
        LOG(INFO)<<results[i];
    }
    ASSERT_TRUE(true);
}

TEST(Test_Queue,test_ptr)
{
    moodycamel::ConcurrentQueue<std::unique_ptr<int>> q;
    int items[] = { 1, 2, 3, 4, 5 };
    auto ptr = std::make_unique<int>();
    *ptr = 123;
    //q.try_dequeue(std::move(ptr));
    q.try_enqueue(std::move(ptr));
    if(!ptr)
    {
        LOG(INFO)<<"unique ptr have empty!";
    }

    decltype(ptr) pop_ptr = std::make_unique<int>();
    bool rst = q.try_dequeue(pop_ptr);
    LOG(INFO)<<"pop ptr "<<*pop_ptr;
    ASSERT_TRUE(true);
}

TEST(Test_Queue,test_class)
{
    moodycamel::ConcurrentQueue<std::unique_ptr<SampleClass>> q;
    
    auto ptr = std::make_unique<SampleClass>();
    //q.try_dequeue(std::move(ptr));
    q.try_enqueue(std::move(ptr));
    if(!ptr)
    {
        LOG(INFO)<<"unique ptr have empty!";
    }
    q.try_dequeue(ptr);    
 
    ASSERT_TRUE(true);
}

using ShareQueue = moodycamel::ConcurrentQueue<std::shared_ptr<SampleClass>>;
using ObjectQueue = moodycamel::ConcurrentQueue<SampleClass>;

TEST(Test_Queue,test_shared_class)
{
    ShareQueue queue;
    auto ptr = std::make_shared<SampleClass>();
    LOG(INFO)<<"ptr ref count "<<ptr.use_count();
    queue.try_enqueue(ptr);
    LOG(INFO)<<"ptr ref count "<<ptr.use_count();
    queue.try_dequeue(ptr);
    LOG(INFO)<<"ptr ref count "<<ptr.use_count();
    if(queue.is_lock_free())
    {
        LOG(INFO)<<"it's really lock-free!";
    }
    std::unordered_map<std::string,std::string> ss;
    ASSERT_TRUE(true);
}
