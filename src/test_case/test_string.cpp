#include "../header.h"

TEST(TestStd, test_string)
{
    std::string_view str0 = "hello world";
    std::string_view str1 = "hello world";
    LOG(INFO) << str0.data();
}
