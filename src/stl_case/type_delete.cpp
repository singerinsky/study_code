#include "../header.h"
#include <type_traits>

std::map<int, std::function<void()> > g_func_map;

template <typename T> void AddToMap(int key, const T& t)
{
    g_func_map.insert(std::make_pair(key, [ & ]()
    {
        return t;
    }));
}
//ERROR ,这里没有用返回值
template <typename T> T GetFromMap(int key)
{
    static T t;
    auto itr = g_func_map.find(key);
    if (itr != g_func_map.end())
    {
        itr->second();
    }
    return t;
}

TEST(Test_std, TypeDel)
{
    AddToMap(1, 1);
    int value = GetFromMap<int>(1);
    LOG(INFO) << "get value from map:" << value;
}

class CallA
{
public:
    void Do() const
    {
        LOG(INFO) << "call a";
    }
};

class CallB
{
public:
    void Do() const
    {
        LOG(INFO) << "call b";
    }

};
std::unordered_map<int, std::function<void()>> g_class_map;

template <typename T> void AddClassToMap(int key, T t)
{
    g_class_map.insert(std::make_pair(key, [ = ]()
    {
        t.Do();
    }));
}
//ERROR ,这里没有用返回值
void DoFromMap(int key)
{

    auto itr = g_class_map.find(key);
    if (itr != g_class_map.end())
    {
        itr->second();
    }
}



TEST(Test_std, TypeCall)
{
    AddClassToMap(1, CallA());
    AddClassToMap(2, CallB());
    DoFromMap(1);
    DoFromMap(2);
}