#include "../header.h"
#include <algorithm>
#include <typeinfo>
#include "../util/class_sample.h"

TEST(Test_std, lambda)
{
    SampleClass object;
    object.SetId(1);
    LOG(INFO) << "Start define lambda";

    auto call = [ = ](int x)
    {
        LOG(INFO) << "x:" << x;
        LOG(INFO) << object.GetId();
    };

    LOG(INFO) << typeid(call).name();
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    for (auto& itr : vec)
    {
        call(itr);
    }

    LOG(INFO) << "pass call function to iterator";
    auto call_object = for_each(vec.begin(), vec.end(), call);
    decltype(for_each(vec.begin(), vec.end(), call)) copy = call;
}


