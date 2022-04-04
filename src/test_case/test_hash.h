#ifndef __TEST_HASH_H__
#define __TEST_HASH_H__

#include "../header.h"

//zoo keeper hash 算法
static unsigned int string_hash_djb2(void *str) 
{
    unsigned int hash = 5381;
    int c;
    const char* cstr = (const char*)str;
    while ((c = *cstr++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

TEST(Hash_Test,test001)
{
    std::string name1="guanlei";
    std::string name2="guanxing";
    auto hash_code_1 = string_hash_djb2(const_cast<char*>(name1.c_str()));
    auto hash_code_2 = string_hash_djb2(const_cast<char*>(name2.c_str()));
    LOG(INFO)<<"hash code 1:"<<hash_code_1;
    LOG(INFO)<<"hash code 2:"<<hash_code_2;
}


#endif // __TEST_HASH_H__