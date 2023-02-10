#ifndef D5151FBC_65AE_484E_8D5B_5D48815E382D
#define D5151FBC_65AE_484E_8D5B_5D48815E382D

#include "../header.h"
#include <algorithm>
#include <random>

std::vector<int> sort_test(std::vector<int>& data)
{
    for (int i = 0; i < data.size(); i++)
    {
        int max = data[i];
        for (int j = i + 1; j < data.size(); j++)
        {
            if (max <= data[j])
            {
                max = data[j];
                std::swap(data[i], data[j]);
            }
        }
    }
    return data;
}

std::vector<int> sort_select(std::vector<int>& data)
{
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data.size() - i - 1; j++)
        {
            if (data[j] > data[j + 1])
            {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
    return data;
}

TEST(BaseTest, sort_popple)
{
    std::vector<int> vec{14, 2, 5, 7, 19, 8};
    std::vector<int> new_vec = sort_test(vec);
    for_each(new_vec.begin(), new_vec.end(), [](auto value)
    {
        LOG(INFO) << value;
    });
    LOG(INFO) << "start bubble sort..........";
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);
    new_vec = sort_select(vec);
    for_each(new_vec.begin(), new_vec.end(), [](auto value)
    {
        LOG(INFO) << value;
    });
}

class ObjectTest001: public testing::Test
{
protected:
    virtual    void TearDown()override
    {
        LOG(INFO) << "tear down test!";
    }

    virtual     void SetUp()override
    {
        LOG(INFO) << "set up!!!";
    }

};

TEST_F(ObjectTest001, DefaultConstructor)
{
}
#endif /* D5151FBC_65AE_484E_8D5B_5D48815E382D */
