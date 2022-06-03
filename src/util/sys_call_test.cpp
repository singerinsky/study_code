#include "../header.h"

int get_my_time();

TEST(Sys,hook)
{
    auto value = time(NULL);
    LOG(INFO)<<"after hook"<<value;
    LOG(INFO)<<"after hook"<<get_my_time();
}
