#pragma once
#include "../header.h"
#include "../util/concurrentqueue.h"
#include "../util/class_sample.h"
#include <future>
#include <string_view>

TEST(Test_Queue, test1)
{
    moodycamel::ConcurrentQueue<int> q;
    int items[] = { 1, 2, 3, 4, 5 };
    q.enqueue_bulk(items, 5);


    int results[5];     // Could also be any iterator
    size_t count = q.try_dequeue_bulk(results, 5);
    for (size_t i = 0; i != count; ++i)
    {
        LOG(INFO) << results[i];
    }
    ASSERT_TRUE(true);
}

TEST(Test_Queue, test_ptr)
{
    moodycamel::ConcurrentQueue<std::unique_ptr<int>> q;
    int items[] = { 1, 2, 3, 4, 5 };
    auto ptr = std::make_unique<int>();
    *ptr = 123;
    //q.try_dequeue(std::move(ptr));
    q.try_enqueue(std::move(ptr));
    if (!ptr)
    {
        LOG(INFO) << "unique ptr have empty!";
    }

    decltype(ptr) pop_ptr = std::make_unique<int>();
    bool rst = q.try_dequeue(pop_ptr);
    LOG(INFO) << "pop ptr " << *pop_ptr;
    ASSERT_TRUE(true);
}

TEST(Test_Queue, test_class)
{
    moodycamel::ConcurrentQueue<std::unique_ptr<SampleClass>> q;

    auto ptr = std::make_unique<SampleClass>();
    //q.try_dequeue(std::move(ptr));
    q.try_enqueue(std::move(ptr));
    if (!ptr)
    {
        LOG(INFO) << "unique ptr have empty!";
    }
    q.try_dequeue(ptr);

    ASSERT_TRUE(true);
}

using ShareQueue = moodycamel::ConcurrentQueue<std::shared_ptr<SampleClass>>;
using ObjectQueue = moodycamel::ConcurrentQueue<SampleClass>;

TEST(Test_Queue, test_shared_class)
{
    ShareQueue queue;
    auto ptr = std::make_shared<SampleClass>();
    LOG(INFO) << "ptr ref count " << ptr.use_count();
    queue.try_enqueue(ptr);
    LOG(INFO) << "ptr ref count " << ptr.use_count();
    queue.try_dequeue(ptr);
    LOG(INFO) << "ptr ref count " << ptr.use_count();
    if (queue.is_lock_free())
    {
        LOG(INFO) << "it's really lock-free!";
    }

    ASSERT_TRUE(true);
}

TEST(Test_Queue, test_thread_rw)
{
    moodycamel::ConcurrentQueue<int> int_queue;
    std::thread thread_one([&]()
    {
        int count = 1;
        while (count <= 1000)
        {
            int_queue.try_enqueue(count);
            LOG(INFO) << "Thread in " << count;
            count++;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

    });
    thread_one.detach();
    std::thread thread_two([&]()
    {
        int count = 1;
        while (count <= 1000)
        {
            int value = 0;
            bool rst = int_queue.try_dequeue(value);
            if (rst)
            {
                LOG(INFO) << "Thread out " << count << "value:" << value;
            }
            count++;
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }

    });
    thread_two.detach();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    LOG(INFO) << "COUNT: " << int_queue.size_approx();

    std::future<void> f = std::async(std::launch::async, []()
    {
        LOG(INFO) << "before sleep";
        std::this_thread::sleep_for(std::chrono::seconds(5));
        LOG(INFO) << "after sleep";
    });
}

TEST(Test_Queue, test_loop)
{
    int age = 1;
    while (age <= 10)
    {
        LOG(INFO) << age;
        age = age + 1;
    }
    LOG(INFO) << "final age:" << age;
}


TEST(Test_Queue, test_oushu)
{
    int age = 1;
    while (age <= 10)
    {
        if (age % 2 == 0)
        {
            LOG(INFO) << age;
        }
        age = age + 1;
    }
    LOG(INFO) << "final age:" << age;
}