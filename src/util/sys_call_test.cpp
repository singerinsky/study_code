#include "../header.h"


TEST(Sys,hook)
{
    auto value = time(NULL);
    LOG(INFO)<<"after hook"<<value;
}
