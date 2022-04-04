#ifndef __TEST_THREAD_SAFE_H__
#define __TEST_THREAD_SAFE_H__
#include "../header.h"
#include <memory>
#include <mutex>
template<class T>
class threadsafe_list
{
    struct node{
        std::mutex m;
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
        node():next(){
        }
        node(const T& value):data(std::make_shared<T>(value))
        {}
    };
    node head;
  public:
    threadsafe_list() {}
    ~threadsafe_list() {
      remove_if([](const node &) { return true; });
    }
    threadsafe_list(const threadsafe_list &other) = delete;
    threadsafe_list &operator=(const threadsafe_list &other) = delete;
    void push_front(const T &value) {
      std::unique_ptr<node> new_node(new node(value));
      std::lock_guard<std::mutex> lk(head.m);
      new_node->next = std::move(head.next);
      head->next = std::move(new_node);
    }
    template<typename Function>
    void for_each(Function f)
    {
        node* current = &head;
        std::unique_lock<std::mutex> lk(head.m);
        while(node* const next = current->next.get())
        {
            std::unique_lock<std::mutex> next_lk(next->m);
            lk.unlock();
            f(*next->data);
            current = next;
            lk=std::move(next_lk);
        }
    }
    template<typename Predicate>
    void remove_if(Predicate p)
    {
        std::unique_lock<std::mutex> lk(head.m);
        node* current = &head;
        while(node* next = current->next.get())
        {
            std::unique_lock<std::mutex> next_lk(next->m);
            if(p(*next->data))
            {
                std::unique_ptr<node> old_next = std::move(current->next);
                current->next = std::move(next->next);
                next_lk.unlock();
            }else
            {
                lk.unlock();
                current = next;
                lk = std::move(next_lk);
            }
        }
    }
};

TEST(Test_SAFE_THREAD,test_001)
{
    threadsafe_list<int> list;

}

#endif // __TEST_THREAD_SAFE_H__